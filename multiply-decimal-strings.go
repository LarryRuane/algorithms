package main

import (
	"fmt"
	"math/rand"
	"strconv"
)

// also reverse so that 1s column is at index 0
func stringToBytes(s string) []byte {
	r := make([]byte, len(s))
	for i := range s {
		r[i] = s[len(s)-1-i] - '0'
	}
	return r
}

// also reverse so result is natural (high order digit on the left)
func bytesToString(b []byte) string {
	r := make([]byte, len(b))
	for i := range b {
		r[i] = b[len(b)-1-i] + '0'
	}
	return string(r)
}

func multiply(num1 string, num2 string) string {
	// same as we do manually, num1 on top, num2 on bottom
	n1 := stringToBytes(num1)
	n2 := stringToBytes(num2)
	// product, least significant digit at index 0
	p := make([]byte, len(num1)+len(num2))
	for i2 := 0; i2 < len(n2); i2++ {
		var carry byte
		var i1 int = 0
		for ; i1 < len(n1); i1++ {
			carry += n2[i2] * n1[i1]
			p[i2+i1] += carry
			carry = p[i2+i1] / 10
			p[i2+i1] %= 10
		}
		p[i2+i1] += carry
		carry = p[i2+i1] / 10
		p[i2+i1] %= 10
	}
	// results array - reverse p (least significant digit on the right, high index)
	r := bytesToString(p)
	// remove leading zeros (except for just "0")
	for len(r) > 1 && r[0] == '0' {
		r = r[1:]
	}
	return r
}

func main() {
	fmt.Println("Hello, playground", multiply("99", "99"), multiply("0", "0"))
	for i := 0; i < 100*1000; i++ {
		ai := int64(rand.Int31())
		bi := int64(rand.Int31())
		a := strconv.FormatInt(ai, 10)
		b := strconv.FormatInt(bi, 10)
		s, _ := strconv.ParseInt(multiply(a, b), 10, 64)
		if s != ai*bi {
			fmt.Println("mismatch", s, ai*bi)
		}
	}
}
