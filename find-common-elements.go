package main

import (
	"fmt"
)

// find and return the common elements in two sorted lists
func findCommon(a, b []int) []int {
	var ai, bi int
	r := make([]int, 0)
	for ai < len(a) && bi < len(b) {
		switch {
		case a[ai] < b[bi]:
			ai++
		case b[bi] < a[ai]:
			bi++
		default:
			// equal, add to result
			r = append(r, a[ai])
			ai++
			bi++
		}
	}
	return r
}

func main() {
	a := []int{2, 3, 5, 10, 15}
	b := []int{3, 4, 10, 20}
	fmt.Println(findCommon(a, b))
}
