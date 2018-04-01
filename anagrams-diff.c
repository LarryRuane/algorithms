#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int uint;

static void calc_hist(char *str, uint *hist) {
    memset(hist, 0, sizeof(uint)*26);
    for (uint i = 0; str[i]; i++) {
        assert(str[i]-'a' < 26);
        hist[str[i]-'a']++;
    }
}

int main() {
    char* a = (char *)malloc(512000 * sizeof(char));
    scanf("%s", a);
    char* b = (char *)malloc(512000 * sizeof(char));
    scanf("%s", b);
    
    uint a_hist[26];
    calc_hist(a, a_hist);
    
    uint b_hist[26];
    calc_hist(b, b_hist);
    
    uint deletes = 0;
    for (uint i = 0; i < 26; i++) {
        if (a_hist[i] > b_hist[i]) {
            deletes += a_hist[i] - b_hist[i];
        } else if (b_hist[i] > a_hist[i]) {
            deletes += b_hist[i] - a_hist[i];
        }
    }
    printf("%u\n", deletes);
    return 0;
}
