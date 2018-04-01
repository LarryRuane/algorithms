#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int uint;

#define MAX_STAIRS 40

unsigned long stairs(
        unsigned long * const dp,
        uint const n)
{
    // if n is zero, we've reached the top, so we've found a way!
    if (!n) return 1;
    
    // dynamic programming: see if we've computed this already
    assert(n < MAX_STAIRS);
    if (dp[n]) return dp[n];
    
    // nope, must compute (then save)
    unsigned long count = 0;
    if (n >= 1) count += stairs(dp, n-1);
    if (n >= 2) count += stairs(dp, n-2);
    if (n >= 3) count += stairs(dp, n-3);
    return dp[n] = count;
}

int main() {
    uint s; 
    scanf("%u", &s);
    for(uint a0 = 0; a0 < s; a0++){
        uint n; 
        scanf("%u", &n);
        // dynamic programming (cache answers)
        unsigned long dp[MAX_STAIRS];
        memset(dp, 0, sizeof(dp));
        printf("%lu\n", stairs(dp, n));
    }
    return 0;
}
