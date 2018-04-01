#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int p; 
    scanf("%d", &p);
    for(int a0 = 0; a0 < p; a0++){
        int n; 
        scanf("%d", &n);
        if (n == 1) {
            // special case (definition)
            printf("Not prime\n");
            continue;
        }
        int i;
        for (i = 2; i*i <= n; i++) {
            if (n % i == 0) {
                break;
            }
        }
        if (i*i <= n) {
            printf("Not prime\n");
        } else {
            printf("Prime\n");
        }
    }
    return 0;
}
