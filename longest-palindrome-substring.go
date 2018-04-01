package main

import (
	"fmt"
)

// Example:
// We fill in this palindrome table 'p' along the diagonals
// each moving from upper-left to lower-right, first 0,1
// then 1,2;2,3;... (first five are shown below).
//
//     s t a r r a t s
//     0 1 2 3 4 5 6 7
// s 0 t F			F = (p[1,0](t) && s[0]("s") == s[1]("t"))
// t 1 t t F 			F = (p[2,1](t) && s[1]("t") == s[2]("a"))
// a 2 t t t F			F = (p[3,2](t) && s[2]("a") == s[3]("r"))
// r 3 t t t t T		T = (p[4,3](t) && s[3]("r") == s[4]("r"))
// r 4 t t t t t F		F = (p[5,4](t) && s[4]("r") == s[5]("a"))
// a 5 t t t t t t
// t 6 t t t t t t t
// s 7 t t t t t t t t

func longestPalindrome(s string) string {
	// p[r][c] is true if s[r:c+1] (substring from r to c) is a palindrome
	p := make([][]bool, len(s))

	// the lower-left half of the table is all true (r is row, c is column)
	for r := 0; r < len(s); r++ {
		for c := 0; c <= r; c++ {
			p[r] = append(p[r], true)
		}
	}
	var maxlen, maxc, maxr int
	// for each diagonal
	for c := 1; c < len(s); c++ {
		// for each entry on this diagonal
		for r := 0; r < len(s)-c; r++ {
			// The range r to c+r is a palindrome if the substring with the
			// first and last characters eliminated (kiddycorner table entry
			// down one row and to the left one column) is a palindrome,
			// and the first and last characters of this range match.
			p[r] = append(p[r], p[r+1][c+r-1] && (s[r] == s[c+r]))
			//fmt.Println(c, r, s[r], s[c+r], p[r+1][c+r-1], p[r][c+r], maxlen)
			if p[r][c+r] && maxlen < c {
				maxlen = c
				maxc = r
				maxr = c + r
			}
		}
	}
	return s[maxc : maxr+1]
}

func printLongest(s string) {
	fmt.Println(s, longestPalindrome(s))
}

func main() {
	printLongest("a")
	printLongest("aa")
	printLongest("aba")
	printLongest("abba")
	printLongest("abcba")
	printLongest("abcbca")

	// on leetcode, my previous implementation reached time limit with this (it now passes):
	printLongest("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
}
