package main

// Given a rotated sorted array, find the index of the rotation point
// (the index of the smallest value). I was given this as a google
// phone screen question.

import (
	"fmt"
	"sort"
)

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

func main() {
	fmt.Println(find_rotate_index([]int{8, 10, 11, 2, 3, 4, 5}))
	fmt.Println(find_rotate_index([]int{2, 3, 4, 5}))
	fmt.Println(find_rotate_index([]int{8, 10, 11, 2}))
	fmt.Println(find_rotate_index([]int{8, 2, 3, 4, 5}))
	a := make([]int, 1000)
	for i := 0; i < len(a); i++ {
		j := 777 + i
		a[j%len(a)] = i
	}
	fmt.Println(find_rotate_index(a))
}
