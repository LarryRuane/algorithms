#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int index_t;
typedef unsigned int value_t;

struct heap {
    index_t nitem;
    index_t size;
    value_t *a;
};

static bool le(value_t a, value_t b) { return a <= b; }
static bool ge(value_t a, value_t b) { return a >= b; }

static void heap_add(
        struct heap *h,
        bool (*cmp)(index_t a, index_t b),
        value_t const v)
{
    assert(h->nitem < h->size);
    index_t i = h->nitem++;
    while (i) {
        index_t parent = (i-1)/2;
        if (cmp(h->a[parent], v)) {
            break;
        }
        assert(i < h->nitem);
        h->a[i] = h->a[parent];
        i = parent;
    }
    assert(i < h->nitem);
    h->a[i] = v;
}

static value_t heap_remove(
        struct heap *h,
        bool (*cmp)(index_t a, index_t b))
{
    assert(h->nitem);
    value_t r = h->a[0];
    if (--h->nitem == 0) {
        return r;
    }
    // logically we're first moving this value to a[0]
    value_t v = h->a[h->nitem];
    index_t i = 0;
    while (true) {
        assert(i < h->nitem);
        index_t lchild = (i*2)+1;
        if (lchild >= h->nitem) {
            break;
        }
        index_t rchild = lchild+1;
        index_t next_i;
        if (rchild >= h->nitem ||
            cmp(h->a[lchild], h->a[rchild])) {
            next_i = lchild;
        } else {
            next_i = rchild;
        }
        if (cmp(v, h->a[next_i])) {
            break;
        }
        assert(i < h->nitem);
        h->a[i] = h->a[next_i];
        i = next_i;
    }
    assert(i < h->nitem);
    h->a[i] = v;
    return r;
}


int main() {
    int n;
    scanf("%u", &n);
    
    // two heaps, one with values below the median (root is max),
    // the other above the median (root is min);
    struct heap below;
    below.nitem = 0;
    below.size = (n+1)/2 + 1;
    below.a = malloc(sizeof(value_t) * below.size);
    
    // below the median, root is min (le than all others)
    struct heap above;
    above.nitem = 0;
    above.size = (n+1)/2 + 1;
    above.a = malloc(sizeof(value_t) * above.size);
    
    double median = 0;
    for (int a_i = 0; a_i < n; a_i++){
        value_t v;
        scanf("%u", &v);
        if (v < median) {
            heap_add(&below, ge, v);
        } else {
            heap_add(&above, le, v);
        }
        
        // now balance the two heaps (their nitems now may differ by
        // at most 2, but adjust so they differ by at most 1)
        if (below.nitem > above.nitem) {
            if (below.nitem == above.nitem+1) {
                median = below.a[0];
                printf("%.1f\n", median);
                continue;
            }
            assert(below.nitem == above.nitem+2);
            // transfer greatest value below to smallest above
            value_t v = heap_remove(&below, ge);
            heap_add(&above, le, v);
        } else if (below.nitem < above.nitem) {
            if (above.nitem == below.nitem+1) {
                median = above.a[0];
                printf("%.1f\n", median);
                continue;
            }
            assert(above.nitem == below.nitem+2);
            // transfer smallest value above to greatest below
            value_t v = heap_remove(&above, le);
            heap_add(&below, ge, v);
        }
        assert(above.nitem == below.nitem);
        median = (double)(below.a[0] + above.a[0]) / 2;
        printf("%.1f\n", median);
    }
    free(below.a);
    free(above.a);
    return 0;
}
