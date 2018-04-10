package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

// element of the linked-list of values (linked by index, not pointer)
type Llist struct {
	next  int
	value int
}

// Return a random permuation of n integers, each in the range 0..m-1
// using Floyd's algorithm (see Programming Pearls by Jon Bentley).
//
// Each iteration of the loop adds each new entry to a linked list,
// either to the beginning (if the random value r isn't already present)
// or it adds the index i after the existing entry.
//
// The linked list is allocated as a single array, since its length, n,
// is known, and this is more efficient than allocating each list entry
// dynamically. The "pointers" are indices into this array.
//
// The 'exist' map allows quick determination of whether the random
// value r is already present in the list (if so, the content of the
// map entry is the index of that existing entry in the linked list
// array), rather than having to linearly search the linked list.

func rand_perm(n int, m int) []int {
	llist := make([]Llist, n)
	exist := make(map[int]int, n)
	var llist_head int
	for j := range llist {
		i := j + m - n
		// example: m=52, n=5: r = 0..47, 0..48, 0..49, 0, 50, 0,51
		r := rand.Intn(i + 1)
		llist_i, found := exist[r]
		if found {
			// r is already present, so insert index i after r's position
			exist[i] = j
			llist[j].value = i
			llist[j].next = llist[llist_i].next
			llist[llist_i].next = j
		} else {
			// r is not present, so insert it at the beginning of the array
			exist[r] = j
			llist[j].value = r
			llist[j].next = llist_head
			llist_head = j
		}
	}
	results := make([]int, n)
	for i := range results {
		results[i] = llist[llist_head].value
		llist_head = llist[llist_head].next
	}
	return results
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	//rand.Seed(2)
	if len(os.Args) < 2 || len(os.Args) > 3 {
		fmt.Println("usage: perm nvalue [range]")
		os.Exit(1)
	}
	n, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("bad unsigned integer", err, os.Args[1])
		os.Exit(1)
	}
	if n < 0 {
		fmt.Println("bad unsigned integer", os.Args[1])
		os.Exit(1)
	}
	m := n
	if len(os.Args) > 2 {
		m_arg, err := strconv.Atoi(os.Args[2])
		if err != nil {
			fmt.Println("bad unsigned integer", err, os.Args[2])
			os.Exit(1)
		}
		if m_arg < 0 {
			fmt.Println("bad unsigned integer", os.Args[2])
			os.Exit(1)
		}
		if m_arg < n {
			fmt.Println("range must be <= nvalues")
			os.Exit(1)
		}
		m = m_arg
	}
	results := rand_perm(n, m)

	for i := range results {
		fmt.Printf("%d ", results[i])
	}
	fmt.Println()
}
