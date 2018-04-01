#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int uint;

typedef struct stack_item_s {
    struct stack_item_s *next;
    int value;
} stack_item_t;

static void stack_push(stack_item_t **top, int value) {
    stack_item_t *new_item = malloc(sizeof(stack_item_t));
    new_item->value = value;
    new_item->next = *top;
    *top = new_item;
}

static int stack_pop(stack_item_t **top) {
    assert(*top); // should not be empty
    stack_item_t *top_item = *top;
    *top = top_item->next;
    int r = top_item->value;
    free(top_item);
    return r;
}

// pop all entries off the enqueue stack and push them
// onto the dequeue stack
static void move(
        stack_item_t **stack_enq,
        stack_item_t **stack_deq)
{
    assert(!(*stack_deq));
    while (*stack_enq) {
        int value = stack_pop(stack_enq);
        stack_push(stack_deq, value);
    }
}

int main() {
    uint nquery;
    scanf("%u", &nquery);
    
    stack_item_t *stack_enq = NULL;
    stack_item_t *stack_deq = NULL;
    
    for (uint i = 0; i < nquery; i++){
        uint request;
        scanf("%u", &request);
        int value;
        switch (request) {

            // enqueue
            case 1:
                scanf("%d", &value);
                stack_push(&stack_enq, value);
                break;
                
            // dequeue (and discard)
            case 2:
                // if deq empty, move all from enq to deq stack
                if (!stack_deq) {
                    move(&stack_enq, &stack_deq);
                }
                assert(stack_deq);
                (void) stack_pop(&stack_deq);
                break;
                
            // print (but leave) front of queue
            case 3:
                // move all from enq to deq stack
                // if deq empty, move all from enq to deq stack
                if (!stack_deq) {
                    move(&stack_enq, &stack_deq);
                }
                assert(stack_deq);
                printf("%d\n", stack_deq->value);
                break;
        }
    }
    return 0;
}
