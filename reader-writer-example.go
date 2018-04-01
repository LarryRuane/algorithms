package main

import (
	"io"
	"log"
	"math/rand"
)

type r struct {
	remaining int
	next      int
}
type w struct {
	expected int
}

func main() {
	for i := 0; i < 100; i++ {
		// copy this number of bytes
		total := int(rand.Intn(1 << uint(rand.Intn(24))))
		src := r{remaining: total}
		dst := w{}
		written, err := io.Copy(&dst, &src)
		if err != nil {
			log.Fatal(err)
		}
		if written != int64(total) {
			log.Fatal(" written:", written, " total:", total)
		}
		if dst.expected != total {
			log.Fatal(" expected:", dst.expected, " total:", total)
		}
	}
}

// copy incrementing (with wraparound) byte values starting at zero
func (r *r) Read(bs []byte) (n int, err error) {
	if r.remaining == 0 {
		return 0, io.EOF
	}
	// "read" a random number of bytes into bs
	n = rand.Intn(30)
	if n > len(bs) {
		n = len(bs)
	}
	err = nil
	if n > r.remaining {
		n = r.remaining
		err = io.EOF
	}
	for i := 0; i < n; i++ {
		// it's ok that this discards precision
		bs[i] = byte(r.next)
		r.next++
		r.remaining--
	}
	return
}

func (w *w) Write(bs []byte) (n int, err error) {
	// "consume" and check bytes from bs
	for i := range bs {
		if bs[i] != byte(w.expected) {
			log.Fatalf("expected %d got %d\n", w.expected, bs[i])
		}
		w.expected++
	}
	return len(bs), nil
}
