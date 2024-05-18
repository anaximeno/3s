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

#ifndef _3S_QUEUE_HEADER
#define _3S_QUEUE_HEADER

#include "./core.h"
#include "./llist.h"

#define EMPTY_STACK_TOP -1

typedef struct s3_queue_t s3_queue_t;

struct s3_queue_t
{
    /* The size of the queue. */
    unsigned size;

    /* The list were values will be stored into. */
    s3_list_t *list;

    /* Adds a new item to the back of the queue. */
    int (*enqueue)(s3_queue_t *self, s3_value_t value);

    /* Returns the item in the front of the queue, removing it from the queue.
     * If no values are found in the queue, then it returns NULL by default.
     * */
    s3_value_t (*dequeue)(s3_queue_t *self);

    /* Returns the item in the front of the queue, without removing it from the queue.
     * If no values are found in the queue, then it returns NULL by default.
     * */
    s3_value_t (*peek)(s3_queue_t *self);

    /* Returns the length of the queue, which represents how
     * many items are in the queue.
     * */
    size_t (*length)(s3_queue_t *self);

    /* Returns a string representing the items in the queue. */
    char *(*repr)(s3_queue_t *self);

    /* Prints the queue representation to the stdout. */
    void (*display)(s3_queue_t *self);
};

/* Adds a new item to the back of the queue. */
extern int s3_queue_enqueue(s3_queue_t *queue, s3_value_t value);

/* Returns the item in the front of the queue, removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern s3_value_t s3_queue_dequeue(s3_queue_t *queue);

/* Returns the item in the front of the queue, without removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern s3_value_t s3_queue_peek(s3_queue_t *queue);

/* Returns the length of the queue, which represents how
 * many items are in the queue.
 * */
extern size_t s3_queue_length(s3_queue_t *queue);

/* Returns a string representing the items in the queue. */
extern char *s3_queue_repr(s3_queue_t *queue);

/* Prints the queue representation to the stdout. */
extern void s3_queue_display(s3_queue_t *self);

/* Creates and returns a new queue. */
extern s3_queue_t *s3_new_queue();

/* Deallocates the memory used in the queue. */
extern void s3_queue_free(s3_queue_t **queue);

#endif
