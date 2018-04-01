#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int uint;

int main() {
    uint n; 
    scanf("%u", &n);
    uint answer = 0;
    for(uint a_i = 0; a_i < n; a_i++){
        // the pair of values will cancel each other out!
        uint value;
        scanf("%u", &value);
        answer ^= value;
    }
    printf("%u\n", answer);
    return 0;
}
