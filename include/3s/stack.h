/* MIT License
 *
 * Copyright (c) 2022 Anaxímeno Brito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#ifndef _3S_STACK_HEADER
#define _3S_STACK_HEADER

#include "./core.h"
#include "./llist.h"

#define EMPTY_STACK_TOP -1

typedef struct s3_stack_t s3_stack_t;

struct s3_stack_t {
    /* The top of the stack. */
    int top;

    /* The size of the stack. */
    unsigned size;

    /* The list were values will be stored into. */
    s3_list_t* list;

    /* Adds a new item to the top of the stack. */
    int (*push) (s3_stack_t* self, s3_value_t value);

    /* Returns the item in the top of the stack, removing it from the stack.
     * If no values are found in the stack, then it returns NULL by default.
     * */
    s3_value_t (*pop) (s3_stack_t* self);

    /* Returns the length of the stack, which represents how
     * many items are in the stack.
     * */
    size_t (*length) (s3_stack_t* self);

    /* Returns a string representing the items in the stack. */
    char* (*repr) (s3_stack_t* self);

    /* Prints the stack representation to the stdout. */
    void (*display) (s3_stack_t* self);
};

/* Adds a new item to the top of the stack. */
extern int s3_stack_push(s3_stack_t* stack, s3_value_t value);

/* Returns the item in the top of the stack, removing it from the stack.
 * If no values are found in the stack, then it returns NULL by default.
 * */
extern s3_value_t s3_stack_pop(s3_stack_t* stack);

/* Returns the length of the stack, which represents how
 * many items are in the stack.
 * */
extern size_t s3_stack_length(s3_stack_t* stack);

/* Returns a string representing the items in the stack. */
extern char* s3_stack_repr(s3_stack_t* stack);

/* Prints the stack representation to the stdout. */
extern void s3_stack_display(s3_stack_t* self);

/* Creates and returns a new stack. */
extern s3_stack_t* s3_new_stack();

/* Deallocates the memory used in the stack. */
extern void s3_stack_free(s3_stack_t** stack);

#endif
