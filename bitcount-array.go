package main

import "fmt"

// pc[i] is the population count of i.
var pc [256]byte

func main() {
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
	for i := 0; i < 10; i++ {
		fmt.Println(i, pc[i])
	}
	fmt.Println(255, pc[255])
}
