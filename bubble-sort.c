#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int n; 
    scanf("%d", &n);
    int *a = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
       scanf("%d", &a[i]);
    }
    int totalswaps = 0;
    int limit = n-1; // optimization as end of array becomes sorted
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < limit; i++) {
            if (a[i] > a[i+1]) {
                int tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
                done = false;
                totalswaps++;
            }
        }
        limit--;
    }
    printf("Array is sorted in %d swaps.\n", totalswaps);
    printf("First Element: %d\n", a[0]);
    printf("Last Element: %d\n", a[n-1]);
    return 0;
}
