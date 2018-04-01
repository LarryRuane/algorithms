package main

import (
	"fmt"
)

func main() {
	var m, n int
	fmt.Scan(&m, &n)
	// read in the magazine
	magazine := make(map[string]int)
	for i := 0; i < m; i++ {
		var word string
		fmt.Scan(&word)
		magazine[word]++
	}
	// for each word in the note, remove it from the magazine
	for i := 0; i < n; i++ {
		var word string
		fmt.Scan(&word)
		if magazine[word] == 0 {
			// not enough of this word in the magazine
			fmt.Println("No")
			return
		}
		magazine[word]--
	}
	fmt.Println("Yes")
}
