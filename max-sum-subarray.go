package main

// Kadane's algorithm - find maximum sum subarray
// https://www.youtube.com/watch?v=kekmCQXYwQ0

import (
	"fmt"
)

func max_sum(a []int) (int, int, int) {
	var max_ending_here, max_overall, start, end, s int
	for i := 0; i < len(a); i++ {
		max_ending_here += a[i]
		if max_overall < max_ending_here {
			max_overall = max_ending_here
			start = s
			end = i + 1
		}
		if max_ending_here < 0 {
			max_ending_here = 0
			s = i + 1
		}

	}
	return max_overall, start, end
}

func main() {
	a := []int{5, -2, -1, 8, 6}
	fmt.Println(max_sum(a))
	a = []int{4, -3, -2, 2, 3, 1, -2, -3, 4, 2, -6, -3, -1, 3, 1, 2}
	fmt.Println(max_sum(a))
	a = []int{}
	fmt.Println(max_sum(a))
	a = []int{-3}
	fmt.Println(max_sum(a))
}
