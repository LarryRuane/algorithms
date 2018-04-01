package main

import (
	"fmt"
)

// returns the index of the two array entries that multiply to the target
func find_two(target int, a []int) (int, int, bool) {
	// the map index is a (nonzero) value we've previously seen;
	// the content is one higher than the index that value appeared
	// at (so also nonzero); content zero means not present
	m := make(map[int]int)
	for i := range a {
		if a[i] == 0 || target%a[i] != 0 {
			// this value can't be of any use to us
			continue
		}
		// needed value seen previously?
		if p := m[target/a[i]]; p > 0 {
			return p - 1, i, true
		}
		// 0 is a legal index, so translate it to 1
		m[a[i]] = i + 1
	}
	return 0, 0, false
}

func main() {
	a := []int{1, 3, 3, 0, 2, 4, 3, 5}
	target := 9
	i0, i1, ok := find_two(target, a)
	if !ok {
		fmt.Println("not found:", target)
	} else {
		fmt.Printf("a[%d]=%d times a[%d]=%d equals %d\n",
			i0, a[i0], i1, a[i1], target)
	}
}
