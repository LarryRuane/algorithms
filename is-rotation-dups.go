package main

import (
	"fmt"
)

// this version handles duplicates
func is_rotation(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	var ai int
	for ai = 0; ai < len(a); ai++ {
		if a[ai] == b[0] {
			aj := ai
			// we've already checked b[0], so start at b[1]
			var bj int
			for bj = 1; bj < len(b); bj++ {
				aj++
				if aj >= len(a) {
					aj = 0
				}
				if a[aj] != b[bj] {
					// this ai doesn't work
					break
				}
			}
			if bj < len(b) {
				// this ai doesn't work, try the next one
				continue
			}
			return true
		}
	}
	return false
}

func main() {
	a := []int{1, 2, 3, 4, 5, 6, 7}
	b := []int{3, 4, 5, 6, 7, 1, 2}
	fmt.Println(is_rotation(a, b))
	d := []int{1, 2, 3, 4, 3, 6, 7}
	e := []int{3, 4, 3, 6, 7, 1, 2}
	fmt.Println(is_rotation(d, e))
	f := []int{1, 2, 3, 4, 3, 6, 7}
	g := []int{3, 6, 7, 1, 2, 3, 4}
	fmt.Println(is_rotation(f, g))
	h := []int{1, 2, 3}
	i := []int{4, 6, 7}
	fmt.Println(is_rotation(h, i))
}
