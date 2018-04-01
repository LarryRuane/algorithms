#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

struct node {
    unsigned count[26];
    struct node *child[26];
};

static struct node *
alloc_node(void)
{
    struct node *p = malloc(sizeof(struct node));
    memset(p, 0, sizeof(struct node));
    return p;
}

static void
free_node(struct node *p)
{
    for (unsigned i=0; i<26; i++) {
        if (p->child[i]) {
            free_node(p->child[i]);
        }
    }
    free(p);
}

int main() {
    unsigned n; 
    scanf("%u", &n);

    char op[21];
    char contact[21];

    struct node *root = alloc_node();
    
    for (int a0 = 0; a0 < n; a0++) {
        scanf("%s %s", op, contact);
        if (!strcmp(op, "add")) {
            struct node *p = root;
            for (unsigned i = 0;; i++) {
                unsigned const char_index = contact[i]-'a';
                assert(char_index < 26);
                p->count[char_index]++;
                if (!contact[i+1]) {
                    // this is the last char of the add string
                    break;
                }
                // not the end of the string, need a child
                if (!p->child[char_index]) {
                    // need to allocate this child pointer
                    p->child[char_index] = alloc_node();
                }
                p = p->child[char_index];
            }
            
        } else if (!strcmp(op, "find")) {
            struct node *p = root;
            unsigned count = 0;
            unsigned i;
            for (i = 0; contact[i]; i++) {
                unsigned const char_index = contact[i]-'a';
                assert(char_index < 26);
                count = p->count[char_index];
                if (!p->child[char_index]) {
                    i++;
                    break;
                }
                p = p->child[char_index];
            }
            if (contact[i]) {
                // the string continues (too long)
                printf("0\n");
                continue;
            }
            printf("%u\n", count);
        } else {
            printf("unknown command %s\n", op);
            assert(0);
        }
    }
    free_node(root);
    return 0;
}
