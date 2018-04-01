package main

import (
	"fmt"
)

type Node struct {
	next  *Node
	value int
}

func removeZeros(head *Node) *Node {
	for p := &head; *p != nil; {
		if (*p).value == 0 {
			// remove (unlink) this item
			(*p) = (*p).next
		} else {
			// keep this item, advance pointer
			p = &(*p).next
		}
	}
	return head
}

func main() {
	var a [5]Node
	a[0].value = 0
	a[0].next = &a[1]
	a[1].value = 0
	a[1].next = &a[2]
	a[2].value = 77
	a[2].next = &a[3]
	a[3].value = 0
	a[3].next = &a[4]
	a[4].value = 55
	a[4].next = nil
	head := &a[0]

	fmt.Print("input: ")
	for p := head; p != nil; p = p.next {
		fmt.Print(p.value, " ")
	}
	head = removeZeros(head)
	fmt.Print("\nresult: ")
	for p := head; p != nil; p = p.next {
		fmt.Print(p.value, " ")
	}
	fmt.Println("")
}
