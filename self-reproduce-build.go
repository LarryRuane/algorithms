package main

import (
	"fmt"
	"io/ioutil"
)

func main() {
	d, err := ioutil.ReadFile("tmp")
	if err != nil {
		panic(err)
	}
	for _, c := range d {
		switch c {
		case '\'':
			fmt.Printf("\t'\\'',\n")
		case '\\':
			fmt.Printf("\t'\\\\',\n")
		case '\n':
			fmt.Printf("\t'\\n',\n")
		case '\t':
			fmt.Printf("\t'\\t',\n")
		default:
			fmt.Printf("\t'%c',\n", c)
		}
	}
}
