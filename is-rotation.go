package main

import (
	"fmt"
)

func is_rotation(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	var ai int
	for ai = 0; ai < len(a); ai++ {
		if a[ai] == b[0] {
			break
		}
	}
	if ai >= len(a) {
		return false
	}
	// we've already checked b[0], so start at b[1]
	for bi := 1; bi < len(b); bi++ {
		ai++
		if ai >= len(a) {
			ai = 0
		}
		if a[ai] != b[bi] {
			return false
		}
	}
	return true
}

func main() {
	a := []int{1, 2, 3, 4, 5, 6, 7}
	b := []int{3, 4, 5, 6, 7, 1, 2}
	fmt.Println(is_rotation(a, b)) // true
	c := []int{1, 2, 3}
	d := []int{4, 5, 6}
	fmt.Println(is_rotation(c, d)) // false
}
