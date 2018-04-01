package main

import (
	"fmt"
	"math/rand"
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
	// poker hand
	fmt.Println(randPerm(5, 52))
}
