#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define GRID_MAX 9

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct grid_s {
    uchar g[GRID_MAX][GRID_MAX];
} grid_t;

static uint calc_region(
        uint n,
        uint m,
        grid_t *grid,
        grid_t *seen,
        int i,
        int j)
{
    if (i < 0 || i >= n || j < 0 || j >= m) {
        // out of bounds
        return 0;
    }
    
    // seen is for performance, also prevents infinite recursion
    if (seen->g[i][j]) {
        return 0;
    }
    seen->g[i][j] = 1;
    
    if (!grid->g[i][j]) {
        return 0;
    }
    uint c = 1; // this cell is part of the region
    c += calc_region(n, m, grid, seen, i-1, j-1);
    c += calc_region(n, m, grid, seen, i-1, j+0);
    c += calc_region(n, m, grid, seen, i-1, j+1);
    c += calc_region(n, m, grid, seen, i+0, j-1);
    c += calc_region(n, m, grid, seen, i+0, j+0);
    c += calc_region(n, m, grid, seen, i+0, j+1);
    c += calc_region(n, m, grid, seen, i+1, j-1);
    c += calc_region(n, m, grid, seen, i+1, j+0);
    c += calc_region(n, m, grid, seen, i+1, j+1);
    return c;
}

int main() {
    uint n; 
    scanf("%u", &n);
    assert(n <= GRID_MAX);
    uint m; 
    scanf("%u", &m);
    assert(m <= GRID_MAX);
    
    grid_t grid;
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < m; j++) {
            uint v;
            scanf("%u", &v);
            assert(v <= 1);
            grid.g[i][j] = v;
        }
    }
    
    // scan top-down, left-right; when we hit the upper-left
    // corner of a region, calc_region() will use DFS to find
    // the rest of the region (and return its size)
    grid_t seen;
    memset(&seen, 0, sizeof(seen));
    uint max_region_count = 0;
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < m; j++) {
            uint c = calc_region(n, m, &grid, &seen, i, j);
            if (max_region_count < c) {
                max_region_count = c;
            }
        }
    }
    printf("%u\n", max_region_count);
    return 0;
}
