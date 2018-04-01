package main

import (
	"fmt"
)

func most_frequent(a []int) (int, int) {
	var max int
	var v int
	m := make(map[int]int, len(a))
	for i := range a {
		m[a[i]]++
		if max < m[a[i]] {
			v = a[i]
			max = m[v]
		}
	}
	return v, max
}

func main() {
	a := []int{1, 3, 2, 3, 3, 2}
	v, n := most_frequent(a)
	fmt.Println("value", v, "appears", n, "times")
}
