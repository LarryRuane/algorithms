#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int uint_t;
typedef unsigned long int ulong_t;

ulong_t total(
    uint_t const remaining,
    uint_t const * const coin,
    uint_t const ncoin,
    uint_t const index,
    long int *cache)
{
    if (index >= ncoin) {
        return 0;
    }
    assert(remaining);
    uint_t n = remaining;
    ulong_t count = 0;
    assert(n);
    
    // dynamic programming:
    if (cache[((n-1)*ncoin)+index] >= 0) {
        return cache[((n-1)*ncoin)+index];
    }
    for (uint_t i = 0;; i++) {
        count += total(n, coin, ncoin, index+1, cache);
        if (n < coin[index]) {
            break;
        }
        n -= coin[index];
        if (!n) {
            count++;
            break;
        }
    }
    return cache[((remaining-1)*ncoin)+index] = count;
}
    
int main() {
    uint_t n; 
    uint_t m; 
    scanf("%u %u", &n, &m);
    uint_t *coin = malloc(sizeof(uint_t) * m);
    for (uint_t coin_i = 0; coin_i < m; coin_i++){
        scanf("%u",&coin[coin_i]);
        assert(coin[coin_i] <= 50);
    }
    
    // dynamic programming: set initial value to invalid
    long int *cache = malloc(sizeof(long int) * n * m);
    for (uint_t i = 0; i < n*m; i++) {
        cache[i] = -1;
    }
    printf("%lu\n", total(n, coin, m, 0, cache));
    
    free(coin);
    free(cache);
    return 0;
}
