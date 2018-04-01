#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef unsigned int uint;
typedef uint nodeid_t;

static inline bool is_power_of_2(uint i) {
    return !(i & (i-1));
}

// vector: simple expandable array of uint (somewhat like c++)
typedef struct vector_s {
    uint *a;
    uint len;
} vector_t;

static void vector_init(vector_t *v) {
    v->a = malloc(0);
    v->len = 0;
}

static void vector_free(vector_t *v) {
    free(v->a);
}

static void vector_add(vector_t *v, uint i) {
    if (is_power_of_2(v->len)) {
        uint len = v->len ? v->len*2 : 1;
        v->a = realloc(v->a, sizeof(uint)*len);
    }
    v->a[v->len++] = i;
}

typedef struct node_s {
    vector_t neighbor;  // list of immediate neighbors (indices)
    int distance;       // from start; initially -1 which means no path
} node_t;

int main() {

    uint nquery;
    scanf("%u", &nquery);
    for (uint query_i = 0; query_i < nquery; query_i++) {
        uint nnode, nedge;
        scanf("%u%u", &nnode, &nedge);
        node_t * const node = calloc(nnode, sizeof(node_t));
        for (uint node_i = 0; node_i < nnode; node_i++) {
            node_t *n = &node[node_i];
            vector_init(&n->neighbor);
            n->distance = -1;
        }
        
        // an edge can exist between any pair of nodes
        for (uint edge_i = 0; edge_i < nedge; edge_i++) {
            nodeid_t node1, node2;
            scanf("%u%u", &node1, &node2);
            
            // zero-based indexing is more convenient
            assert(node1);
            node1--;
            assert(node1 < nnode);
            
            assert(node2);
            node2--;
            assert(node2 < nnode);
            
            vector_add(&node[node1].neighbor, node2);
            vector_add(&node[node2].neighbor, node1);
        }
        
        nodeid_t start_node;
        scanf("%u", &start_node);
        assert(start_node);
        start_node--;
        assert(start_node < nnode);
        
        vector_t todo;
        vector_init(&todo);
        uint todo_next = 0;
        
        node[start_node].distance = 0;
        vector_add(&todo, start_node);
        
        // main loop; moving outward from start like a "wave"
        // (breadth-first) ensures that the first time we encounter
        // a node, we've reached it by the shortest path
        // (no need to ever do a "min" calculation)
        while (todo_next < todo.len) {
            // remove next (now current) node (c) from todo list
            node_t *c = &node[todo.a[todo_next++]];
            assert(c->distance >= 0);
            for (uint i = 0; i < c->neighbor.len; i++) {
                node_t *neighbor = &node[c->neighbor.a[i]];
                if (neighbor->distance >= 0) {
                    // we've already reached this node
                    continue;
                }
                // one hop farther from start than current node
                neighbor->distance = c->distance + 6;
                vector_add(&todo, c->neighbor.a[i]);
            }
        }
        
        // done, print results and clean up
        vector_free(&todo);
        for (uint node_i = 0; node_i < nnode; node_i++) {
            node_t *n = &node[node_i];
            if (node_i != start_node) {
                printf("%d ", n->distance);
            }
            vector_free(&n->neighbor);
        }
        printf("\n");
        free(node);
    }
    return 0;
}
