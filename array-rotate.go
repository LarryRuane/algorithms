package main
import "fmt"

func swapArray(a []int) {
    for i := 0; i < len(a)/2; i++ {
        j := len(a)-1-i
        a[i], a[j] = a[j], a[i]
    }
}

func main() {
    var n, r int
    fmt.Scan(&n, &r)
    a := make([]int, n)
    for i := 0; i < n; i++ {
        fmt.Scan(&a[i])
    }
    swapArray(a[0:r])
    swapArray(a[r:n])
    swapArray(a)
    for i := range a {
        if i > 0 {
            fmt.Print(" ")
        }
        fmt.Print(a[i])
    }
    fmt.Println()
}
