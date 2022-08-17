#include "../include/core.h"
#include "../include/stack.h"
#include "../include/llist.h"

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"


static int push_value_to_stack(s3_stack_t* stack, s3_value_t value)
{
    if (stack != NULL) {
        /* Try to create a new list, if not created previously. */
        if (stack->list == NULL) {
            /* Be aware that the function call below could still return NULL,
             * if there's no available space.
             * */
            stack->list = s3_new_list();
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


static s3_value_t pop_value_from_stack(s3_stack_t* stack)
{
    if (stack != NULL) {
        if (stack->list != NULL && stack->list->length > 0) {
            s3_value_t value = stack->list->get(stack->list, stack->top);
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


static size_t length_of_stack(s3_stack_t* stack)
{
    if (stack != NULL)
        return stack->size;
    return 0;
}


static char* stack_repr(s3_stack_t* stack)
__LIST_REPR_ALGORITHM(stack->list, "$[", "]>", "|", FORWARD)


static void stack_display(s3_stack_t* self)
{
    char* repr = stack_repr(self);
    printf("%s", repr);
    free(repr);
}


extern s3_stack_t* s3_new_stack()
{
    s3_stack_t* stack = (s3_stack_t*) malloc(sizeof(s3_stack_t));

    if (stack != NULL) {
        stack->top = EMPTY_STACK_TOP;
        stack->size = 0;
        stack->list = s3_new_list();

        stack->push = &push_value_to_stack;
        stack->pop = &pop_value_from_stack;
        stack->length = &length_of_stack;
        stack->repr = &stack_repr;
        stack->display = &stack_display;
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
