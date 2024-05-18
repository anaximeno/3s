/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (c) 2022 Anaxímeno Brito                                                *
 *                                                                                   *
 * Permission is hereby granted, free of charge, to any person obtaining a copy      *
 * of this software and associated documentation files (the "Software"), to deal     *
 * in the Software without restriction, including without limitation the rights      *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell         *
 * copies of the Software, and to permit persons to whom the Software is             *
 * furnished to do so, subject to the following conditions:                          *
 *                                                                                   *
 * The above copyright notice and this permission notice shall be included in all    *
 * copies or substantial portions of the Software.                                   *
 *                                                                                   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,          *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE       *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER            *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,     *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     *
 * SOFTWARE.                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../include/3s/core.h"
#include "../include/3s/stack.h"
#include "../include/3s/llist.h"

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

/* Adds a new item to the top of the stack. */
extern int ts_stack_push(ts_stack_t *stack, ts_generic_t value)
{
    if (stack != NULL)
    {
        /* Try to create a new list, if not created previously. */
        if (stack->list == NULL)
        {
            /* Be aware that the function call below could still return NULL,
             * if there's no available space.
             * */
            stack->list = ts_new_list();
            stack->size = 0;
            stack->top = EMPTY_STACK_TOP;
        }

        /* If the list was or could be allocated. */
        if (stack->list != NULL)
        {
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
extern ts_generic_t ts_stack_pop(ts_stack_t *stack)
{
    if (stack != NULL)
    {
        if (stack->list != NULL && stack->list->length > 0)
        {
            ts_generic_t popped = stack->list->get(stack->list, stack->top);
            ts_generic_t value = (ts_generic_t)malloc(sizeof(struct ts_generic_t));

            /* Copy bytes from the value popped to the one that will be returned. */
            memcpy(value, popped, sizeof(struct ts_generic_t));

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
extern size_t ts_stack_length(ts_stack_t *stack)
{
    if (stack != NULL)
        return stack->size;
    return 0;
}

/* Returns a string representing the items in the stack. */
extern char *ts_stack_repr(ts_stack_t *stack)
    TS_LIST_REPR_ALGORITHM(
        stack->list,
        "$[",
        "]>",
        "|",
        FORWARD);

/* Prints the stack representation to the stdout. */
extern void ts_stack_display(ts_stack_t *self)
{
    char *repr = ts_stack_repr(self);
    printf("%s", repr);
    free(repr);
}

extern ts_stack_t *ts_new_stack()
{
    ts_stack_t *stack = (ts_stack_t *)malloc(sizeof(ts_stack_t));

    if (stack != NULL)
    {
        stack->size = 0;
        stack->top = EMPTY_STACK_TOP;
        stack->list = ts_new_list();

        /* Associated functions. */
        stack->push = &ts_stack_push;
        stack->pop = &ts_stack_pop;
        stack->length = &ts_stack_length;
        stack->repr = &ts_stack_repr;
        stack->display = &ts_stack_display;
    }

    return stack;
}

extern void ts_stack_free(ts_stack_t **stack)
{
    if (*stack != NULL)
    {
        ts_list_free(&(*stack)->list);
        free(*stack);
        *stack = NULL;
    }
}
