#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned int uint;

#define MAX_N 100000
#define MAX_VALUE 50000

uint a[MAX_N];
bool b[MAX_VALUE+1];

int main() {
    // read input
    uint n;
    scanf("%u", &n);
    assert(n <= MAX_N);
    for (int i = 0; i < n; i++) {
        uint v;
        scanf("%u", &v);
        assert(v);
        assert(v <= MAX_VALUE);
        b[v] = true;
    }
    
    // start grinding
    uint rep = 0;
    while (true) {
        // transfer from b (presence array) back to a (sorted list)
        uint stride = 0;
        bool in_stride = true;
        n = 0;
        for (uint i = 1; i <= MAX_VALUE; i++) {
            if (b[i]) {
                b[i] = false;
                if (!n) {
                   stride = i;
                } else if (in_stride && i - a[n-1] != stride) {
                    in_stride = false;
                }
                a[n++] = i;
            }
        }
        if (!n) {
            break;
        }
        if (in_stride) {
            // shortcut
            assert(a[n-1]/stride == n);
            rep += n;
            break;
        }
        rep++;
        for (uint ai = 0; ai < n-1; ai++) {
            for (uint aj = ai+1; aj < n; aj++) {
                // no unnecessary code here, performance-critical
                b[a[aj] - a[ai]] = true;
            }
        }
    }
    printf("%u\n", rep);
    return 0;
}
