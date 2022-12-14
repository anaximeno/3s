#include "../include/core.h"
#include "../include/stack.h"
#include "../include/llist.h"

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"


/* Adds a new item to the top of the stack. */
extern int s3_stack_push(s3_stack_t* stack, s3_value_t value)
{
    if (stack != NULL) {
        /* Try to create a new list, if not created previously. */
        if (stack->list == NULL) {
            /* Be aware that the function call below could still return NULL,
             * if there's no available space.
             * */
            stack->list = s3_new_list();
            stack->size = 0;
            stack->top = EMPTY_STACK_TOP;
        }

        /* If the list was or could be allocated. */
        if (stack->list != NULL) {
            stack->list->append_back(stack->list, value);
            stack->size += 1;
            stack->top += 1;
#ifdef _MAKE_ROBUST_CHECK
            assert(stack->size == stack->list->length);
            assert(stack->top + 1 == stack->list->length);
#endif /* _MAKE_ROBUST_CHECK */
            return 0;
        }
    }

    return 1;
}


/* Returns the item in the top of the stack, removing it from the stack.
 * If no values are found in the stack, then it returns NULL by default.
 * */
extern s3_value_t s3_stack_pop(s3_stack_t* stack)
{
    if (stack != NULL) {
        if (stack->list != NULL && stack->list->length > 0) {
            s3_value_t popped = stack->list->get(stack->list, stack->top);
            s3_value_t value = (s3_value_t) malloc(sizeof(struct s3_value_t));

            /* Copy bytes from the value popped to the one that will be returned. */
            memcpy(value, popped, sizeof(struct s3_value_t));

            stack->list->remove_at_index(stack->list, stack->top);
            stack->size -= 1;
            stack->top -= 1;
#ifdef _MAKE_ROBUST_CHECK
            assert(stack->size == stack->list->length);
            assert(stack->top + 1 == stack->list->length);
#endif /* _MAKE_ROBUST_CHECK */
            return value;
        }
    }

    return NULL;
}


/* Returns the length of the stack, which represents how
 * many items are in the stack.
 * */
extern size_t s3_stack_length(s3_stack_t* stack)
{
    if (stack != NULL)
        return stack->size;
    return 0;
}


/* Returns a string representing the items in the stack. */
extern char* s3_stack_repr(s3_stack_t* stack)
__LIST_REPR_ALGORITHM(stack->list, "$[", "]>", "|", FORWARD);


/* Prints the stack representation to the stdout. */
extern void s3_stack_display(s3_stack_t* self)
{
    char* repr = s3_stack_repr(self);
    printf("%s", repr);
    free(repr);
}


extern s3_stack_t* s3_new_stack()
{
    s3_stack_t* stack = (s3_stack_t*) malloc(sizeof(s3_stack_t));

    if (stack != NULL) {
        stack->size = 0;
        stack->top = EMPTY_STACK_TOP;
        stack->list = s3_new_list();

        /* Associated functions. */
        stack->push = &s3_stack_push;
        stack->pop = &s3_stack_pop;
        stack->length = &s3_stack_length;
        stack->repr = &s3_stack_repr;
        stack->display = &s3_stack_display;
    }

    return stack;
}

extern void s3_stack_free(s3_stack_t** stack)
{
    if (*stack != NULL) {
        s3_list_free(&(*stack)->list);
        free(*stack);
        *stack = NULL;
    }
}
