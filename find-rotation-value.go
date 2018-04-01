package main

import (
	"fmt"
	"sort"
)

// Given a rotated sorted array, find the index of the rotation point
// (the index of the smallest value). I was given this as a google
// phone screen question.
func find_rotate_index(a []int) int {
	// The function needs to return false for the first part of the
	// range, true beyond that; if the rotation point is to the left
	// of a[i], return true.
	r := sort.Search(len(a), func(i int) bool { return a[i] < a[0] })
	if r == len(a) {
		// special case
		r = 0
	}
	return r
}

// Search for value v in rotated sorted array a, return index of v
// if present (and true), or the index where v would be inserted
// (before the returned index).
func find_value_in_rotated(a []int, v int) (int, bool) {
	r := find_rotate_index(a)
	i := sort.Search(len(a), func(i int) bool { return a[(i+r)%len(a)] >= v })
	j := (i + r) % len(a)
	return j, a[j] == v
}

func main() {
	fmt.Println(find_value_in_rotated([]int{8, 2, 3, 4, 5}, 1))
	fmt.Println(find_value_in_rotated([]int{8, 2, 3, 4, 5}, 4))
	fmt.Println(find_value_in_rotated([]int{1, 2, 3, 4, 5}, 2))
	fmt.Println(find_value_in_rotated([]int{8, 2, 3, 4, 5}, 8))
}
