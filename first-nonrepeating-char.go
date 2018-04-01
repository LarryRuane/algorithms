package main

import (
	"fmt"
)

// return the first non-repeating character in the given string
// or "None" if there are no non-repeating characters
func first_non_repeating(s string) string {
	b := []byte(s)
	m := make(map[byte]int)
	for i := range b {
		m[b[i]]++
	}
	for i := range b {
		if m[b[i]] == 1 {
			return "'" + string(b[i]) + "'"
		}
	}
	return "None"
}

func main() {
	fmt.Println(first_non_repeating("hello"))    // 'h'
	fmt.Println(first_non_repeating("hellho"))   // 'e'
	fmt.Println(first_non_repeating("helleho"))  // 'o'
	fmt.Println(first_non_repeating("heollheo")) // None
}
