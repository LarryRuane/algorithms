#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

// This version does all k rotations in one pass,
// in-place (not using a separate target array).
//
// (In an interview, this is too complex; better to use a
// a separate target array).
int main() {
    unsigned n; 
    unsigned k; 
    scanf("%u %u", &n, &k);
    assert(k > 0);
    unsigned *a = malloc(sizeof(unsigned) * n);
    for (unsigned a_i = 0; a_i < n; a_i++){
       scanf("%u",&a[a_i]);
    }
    unsigned moved = 0;
    unsigned start = 0;
    // every element in the array needs to move
    while (moved < n) {
        unsigned const tmp = a[start];
        unsigned target = start;
        while (true) {
            unsigned source = target + k;
            // source %= n, but this is slightly cheaper:
            if (source >= n) {
                source -= n;
            }
            if (source == start) {
                // we've already copied to this source
                a[target] = tmp;
                assert(moved < n);
                moved++;
                break;
            }
            a[target] = a[source];
            assert(moved < n);
            moved++;
            // next we will copy into the element we just copied from
            target = source;
        }
        start++;
        assert(moved >= n || start < k);
    }
    assert(moved == n);
    for (unsigned a_i = 0; a_i < n;a_i++) {
        printf("%u ", a[a_i]);
    }
    printf("\n");
    free(a);
    return 0;
}
