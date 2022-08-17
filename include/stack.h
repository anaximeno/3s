#ifndef _3S_STACK_HEADER
#define _3S_STACK_HEADER

#include "./core.h"
#include "./llist.h"

typedef struct s3_stack s3_stack;

struct s3_stack {
    /* The top of the stack. */
    int top;

    /* The size of the stack. */
    unsigned size;

    /* The list were values will be stored into. */
    s3_linked_list* list;

    /* Adds a new item to the top of the stack. */
    void (*push) (s3_stack* self, s3_value_t value);

    /* Returns the item in the top of the stack, removing it from the stack.
     * If no values are found in the stack, then it returns NULL by default.
     * */
    s3_value_t (*pop) (s3_stack* self);

    /* Returns the length of the stack, which represents how
     * many items are in the stack.
     * */
    unsigned (*length) (s3_stack* self);

    /* Returns a string representing the items in the stack. */
    char* (*repr) (s3_stack* self);

    /* Prints the stack representation to the stdout. */
    void (*display) (s3_stack* self);
};

/* Creates and returns a new stack. */
extern s3_stack new_stack();

#endif