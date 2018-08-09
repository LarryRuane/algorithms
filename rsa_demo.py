#!/usr/bin/env python3

import sys

def gcd(a, b):
    while b > 0:
        a, b = b, a % b
    return a

def lcm(a, b):
    return a*b // gcd(a, b)

def rsademo(p, q):
    print("secret: p =", p, "q =", q)
    # alice: set up public-private key pair
    n = p*q                 # public modulus
    phi = lcm(p-1, q-1)     # secret, believed to be hard to find from n

    # public exponent e must be relatively prime with phi
    for e in range(3, phi, 2):
        if phi % e is not 0:
            break
    else:
        print('XXXXXX none of 2..{} works for e'.format(phi))
        return

    # derive private key d from e (d is secret)
    # find k such that when we divide by e (to get d), there is no fraction
    # (k is not secret, can be any integer, smaller is more efficient)
    maxk = 2000
    for k in range(1, maxk):
        if ((k*phi)+1) % e is 0:
            break
    else:
        print('XXXXXX none of 1..{} works for k (e={})'.format(maxk, e))
        return
    d = ((k*phi)+1) // e

    print('secret: p =', p, 'q =', q, 'phi =', phi, 'd =', d, 'k =', k)
    print('public: n =', n, 'e =', e)

    # test that bob can send all possible messages
    for m in range(n):
        # bob encrpyts m using alice's public key (e, n)
        c = (m**e) % n
        # alice decrypts c using her private key (d, n)
        dm = (c**d) % n
        #print('m:', m, 'c:', c, ' decrypt:', dm)
        if dm != m:
            print('mismatch m:', m, 'c:', c, ' decrypt:', dm)
            exit(1)

# main
if len(sys.argv) == 3:
    p = int(sys.argv[1])    # secret!
    q = int(sys.argv[2])    # secret!
    rsademo(p, q)
    exit(0)
if len(sys.argv) != 2:
    print('usage: {} [p q] | n'.format(sys.argv[0]))
    exit(0)

primes = (
7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
307, 311, 313,
317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
)

# these seem to be too big to complete in a reasonable amount of time
primes2 = (
409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683,
691, 701, 709, 719, 727,
)

from random import randrange
for i in range(0, int(sys.argv[1])):
    p1 = primes[randrange(0, len(primes))]
    # the two primes must be different
    while True:
        p2 = primes[randrange(0, len(primes))]
        if p1 is not p2: break
    rsademo(p1, p2)
