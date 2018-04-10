package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

// Return a random permuation of n integers, each in the range 0..m-1
//
// Conceptually we have an array of m elements, initialized as a[i] == i
// and we swap the first n entries with a random element to its right;
// the result is the first n entries of the array.
//
// But since m can be large, the array is "virtual;" we use a map
// (hash table) to record only entries that have been swapped; if
// (conceptual) element a[i] hasn't been swapped, then it doesn't
// exist in the map; if elements a[i] and a[j] have been swapped, then
// there will be two map entries, a[i] = j and a[j] = i.

// Get the value in the virtual array at index i
func get(swaps map[int]int, i int) int {
	v, found := swaps[i]
	if found {
		return v
	}
	return i
}

func randPerm(n int, m int) []int {
	swaps := make(map[int]int, n)
	results := make([]int, n)
	for i := 0; i < n; i++ {
		r := i + rand.Intn(m-i)
		// swap a[i] and a[r]
		vi := get(swaps, i)
		vr := get(swaps, r)
		if vi != vr {
			swaps[r] = vi
		}
		results[i] = vr
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
	results := randPerm(n, m)

	for i := range results {
		fmt.Printf("%d ", results[i])
	}
	fmt.Println()
}
