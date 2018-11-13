#!/usr/bin/python3
from hashlib import md5
from random import randrange, seed

# make the run reproducible (good if there is a bug)
seed(0)

# Hash the given string (returns a 32-char hex-digit string)
def hash_string(s):
    # Real hash function is 'skein'; python3 doesn't provide that
    # but this returns the same length as skein (256 bits, 32 bytes)
    return md5(s.encode()).hexdigest()

# On a real system, it would make sense to scale the bloom filter length
# in proportion to the number of unique blockids; since we probably don't
# know that, it could be proportional to the number of volume blocks.
# (Small value like 4 demonstrates collisions, some space not freed!)
bloom_filter_length = 4
print('bloom_filter_length', bloom_filter_length)

# Hash a blockid (itself the result of a hash!) with given seed (i)
# for the bloom filter
# This function is shared by block and slice servers
def bloom_hash(blockid, i):
    m = hex(int(blockid, 16)+i)
    return int(hash_string(m), 16) % bloom_filter_length

# ##################################### BLOCK SERVER:

# A drive (the only one) is modeled as an array of characters;
# the strings stored in 'drive' are not null-terminated
nsector = 20
print('drive sectors', nsector)
drive = [ '' ] * nsector

# We write the 'drive' in a log-structed manner, moving forward with wrap
write_index = 0

# increment (and return) the given write index, with wraparound
def write_index_inc(i):
    i += 1
    if i >= nsector:
        i = 0
    return i

# This is the block server's metadata table, converts a blockid to a physical
# location (index into 'drive') and length (sectors, actually characters)
bs_metadata = { }

# Return True if successful (not out of space)
def bs_write(blockid, data):
    global write_index
    assert(len(data) > 0)
    if blockid in bs_metadata:
        print('bs: dedup: data', data, 'metadata', bs_metadata[blockid])
        return True

    # find a range on the drive large enough for this write
    wi_start = i = write_index
    # how many free sectors we still need
    need = len(data)
    while True:
        d = drive[i]
        if d == '':
            # available
            need -= 1
            if need == 0:
                break
        i = write_index_inc(i)
        if i == wi_start:
            print('bs: no space')
            return False
        if d != '':
            # in-use, start over
            write_index = i
            need = len(data)

    # there is enough space here (starting at write_index)
    print('bs: setting bs_metadata', blockid, 'to drive index', write_index)
    bs_metadata[blockid] = (write_index, len(data))
    for i in range(len(data)):
        # write a single byte (sector) to an available location
        assert(drive[write_index] == '')
        drive[write_index] = data[i]
        write_index = write_index_inc(write_index)
    return True

def bs_read(blockid):
    # the volume shouldn't have a blockid that we don't know about
    assert(blockid in bs_metadata)
    drive_location = bs_metadata[blockid]
    read_index, length = drive_location
    assert(read_index < nsector)
    read_data = ''
    for i in range(length):
        read_data += drive[read_index+i]
    print(read_data)

# if any bit is False, the blockid is not present;
# if all bits are True, the blockid may be present
def bs_bloom_check(nonce, bloom_filter, blockid):
    for i in range(4):
        bloom_index = bloom_hash(blockid, nonce+i)
        if not bloom_filter[bloom_index]:
            return False;
    # all bits are present, we must assume this data is still needed
    return True

# on the real system, it's critical that garbage collection does not occur
# unless and until the block server receives filters from every slice server,
# else data loss!
def bs_garbage_collect(nonce, bloom_filter):
    for blockid, drive_location in list(bs_metadata.items()):
        if bs_bloom_check(nonce, bloom_filter, blockid):
            # this entry may be still in use
            continue
        # we can delete this entry
        print('bs: deleting blockid', blockid)
        del bs_metadata[blockid]
        erase_index, length = drive_location
        for i in range(length):
            # "erase" sector so it is available (write empty string)
            # (this actually done by recycling, which is not modeled here)
            assert(drive[erase_index] != '')
            drive[erase_index] = ''
            erase_index = write_index_inc(erase_index)


# ##################################### SLICE SERVER:

# array indexed by 4k block number, content is blockid
volume_metadata_length = 10
print('volume length', volume_metadata_length)
volume_metadata = [ '' ] * volume_metadata_length

# Write the given variable-length data (string) to the given offset
# (block_offset is analogous to a 4k block number)
def volume_write(block_offset, data):
    if block_offset >= volume_metadata_length:
        print('offset must be less than', volume_metadata_length)
        return False
    blockid = hash_string(data)
    print('ss: write: offset =', block_offset,
        'blockid =', blockid, 'data =', data)
    if bs_write(blockid, data):
        # success (not out of space)
        volume_metadata[block_offset] = blockid
        return True
    return False

# Read and return the given variable-length data (string) the given offset
# (block_offset is analogous to a 4k block number)
def volume_read(block_offset):
    if block_offset >= volume_metadata_length:
        print('offset must be less than', volume_metadata_length)
        return ''
    blockid = volume_metadata[block_offset]
    if blockid == '':
        print('no data at offset', block_offset)
        return ''
    print('ss: read: offset =', block_offset, 'blockid =', blockid)
    bs_read(blockid)

def garbage_collect():
    bloom_filter = [ False ] * bloom_filter_length
    # random start value so that even if one GC run doesn't delete all free
    # entries, the next run may find them
    nonce = randrange(10000)
    for blockid in volume_metadata:
        if blockid == '':
            # this offset was never written
            continue
        for i in range(4):
            bloom_index = bloom_hash(blockid, nonce+i)
            bloom_filter[bloom_index] = True
    bs_garbage_collect(nonce, bloom_filter)

# ##################################### MAIN:

while True:
    try:
        line = input('h[elp] | q[uit] | d[ump] | '
            'w[rite] index string | r[ead] index | g[c] : ').strip().split(' ')
    except KeyboardInterrupt:
        print('')
        break
    except EOFError:
        print('')
        break
    command = line[0]
    if len(command) > 0:
        if command[0] == 'q':
            break
        if command[0] == 'h':
            print('This instructional program simulates the most basic '
                'aspects of Solidfire')
            print('Commands (only first letter of command needed):')
            print('  write volume-offset string (example: w 5 hello_world)')
            print('  read volume-offset')
            print('  gc (garbage_collect)')
            print('  dump (dump entire state of the system)')
            print('  help')
            print('  quit')
            print('')
            print('After each write or gc, the state of the system is dumped')
            print('Note that a write may fail due to out-of-space')
        elif command[0] == 'w':
            if len(line) < 3:
                continue
            i = int(line[1])
            data = line[2]
            volume_write(i, data)
        elif command[0] == 'r':
            if len(line) < 2:
                continue
            i = int(line[1])
            if i >= volume_metadata_length:
                print('i must be less than', volume_metadata_length)
                continue
            volume_read(i)
        elif command[0] == 'g':
            garbage_collect()
        elif command[0] == 'd':
            # dump the state of the system
            print('')
            print('ss: volume:', volume_metadata)
            print('bs: write_index', write_index)
            print('bs: drive:', drive)
            print('bs: metadata:', bs_metadata)
            print('')
