/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef void * env_t;
typedef void const * envc_t;

typedef unsigned int index_t;

/* this heap code is not general because is it assumes the heap contains
 * index values, and it assumes the heap array is initialized to be
 * large enough for all time (as is the case here)
 */
typedef struct heap {
    index_t nitem;
    index_t size;
    index_t *a;
} heap_t;

static void heap_init(heap_t *h, index_t size) {
    h->size = size;
    h->a = malloc(sizeof(h->a)*size);
    h->nitem = 0;
}

static void heap_uninit(heap_t *h) {
    assert(h->a);
    free(h->a);
    h->a = NULL;
}

// append to the end of the array, then "bubble" it upwards
static void heap_add(
        struct heap *h,
        env_t env,
        bool (*lessthan_f)(env_t, index_t, index_t),
        index_t const v)
{
    assert(h->nitem < h->size);
    index_t i = h->nitem++;
    while (i) {
        index_t parent = (i-1)/2;
        if (lessthan_f(env, h->a[parent], v)) {
            break;
        }
        assert(i < h->nitem);
        h->a[i] = h->a[parent];
        i = parent;
    }
    assert(i < h->nitem);
    h->a[i] = v;
}

static index_t heap_remove(
        struct heap *h,
        env_t env,
        bool (*lessthan_f)(env_t, index_t, index_t))
{
    assert(h->nitem);
    index_t const r = h->a[0];
    if (--h->nitem == 0) {
        return r;
    }
    // logically we're first moving this last value to a[0]
    index_t v = h->a[h->nitem];
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
            lessthan_f(env, h->a[lchild], h->a[rchild])) {
            next_i = lchild;
        } else {
            next_i = rchild;
        }
        if (lessthan_f(env, v, h->a[next_i])) {
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

typedef struct range_env {
    int **nums;
    int numsRowSize;
    int *numsColSizes;
    index_t *current;
} range_env_t;

// this actually takes two row indices (which array)
static bool lessthan(envc_t env, index_t row_a, index_t row_b) {
    const range_env_t *re = env;
    assert(row_a < re->numsRowSize);
    assert(row_b < re->numsRowSize);
    assert(re->current[row_a] < re->numsColSizes[row_a]);
    assert(re->current[row_b] < re->numsColSizes[row_b]);
    return re->nums[row_a][re->current[row_a]] <
           re->nums[row_b][re->current[row_b]];
}

#define get_num(i) (nums[i][re.current[i]])

int* smallestRange(int** nums, int numsRowSize, int *numsColSizes, int* returnSize) {
    heap_t heap;
    heap_init(&heap, numsRowSize);

    range_env_t re;
    re.nums = nums;
    re.numsRowSize = numsRowSize;
    re.numsColSizes = numsColSizes;
    // per-row (per-array) indices, init zero, always increasing
    re.current = calloc(numsRowSize, sizeof(index_t));
    int max_value = 0;
    // heap has one element per array, sorted by value at that array's current index 
    for (index_t row = 0; row < numsRowSize; row++) {
        assert(numsColSizes[row] > 0); // could probably remove the need for this
        heap_add(&heap, &re, lessthan, row);
        if (row == 0 || max_value < nums[row][0]) {
            max_value = nums[row][0];
        }
    }
    int *r = malloc(sizeof(int)*2);
    // the best (smallest) we've seen so far, since initially the only so far
    index_t min_row = heap_remove(&heap, &re, lessthan);
    assert(max_value >= get_num(min_row));
    r[0] = get_num(min_row);
    r[1] = max_value;

    // advance the array index that points to the smallest value
    while (++re.current[min_row] < numsColSizes[min_row]) {
        // the new value at min_row may now be the largest value overall
        if (max_value < get_num(min_row)) {
            // we have a new maximum value across all the arrays (at current index)
            max_value = get_num(min_row);
        }
        heap_add(&heap, &re, lessthan, min_row);

        // find what is currently the row with the smallest value
        min_row = heap_remove(&heap, &re, lessthan);
        assert(max_value >= get_num(min_row));
        if (max_value - get_num(min_row) < r[1] - r[0]) {
            // remember this new smallest range
            r[0] = get_num(min_row);
            r[1] = max_value;
        }
    }
    assert(re.current[min_row] == numsColSizes[min_row]);
    
    free(re.current);
    heap_uninit(&heap);
    *returnSize = 2;
    return r;
}
