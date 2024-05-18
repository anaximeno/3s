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

typedef struct ts_queue_t ts_queue_t;

struct ts_queue_t
{
    /* The size of the queue. */
    unsigned size;

    /* The list were values will be stored into. */
    ts_list_t *list;

    /* Adds a new item to the back of the queue. */
    int (*enqueue)(ts_queue_t *self, ts_generic_t value);

    /* Returns the item in the front of the queue, removing it from the queue.
     * If no values are found in the queue, then it returns NULL by default.
     * */
    ts_generic_t (*dequeue)(ts_queue_t *self);

    /* Returns the item in the front of the queue, without removing it from the queue.
     * If no values are found in the queue, then it returns NULL by default.
     * */
    ts_generic_t (*peek)(ts_queue_t *self);

    /* Returns the length of the queue, which represents how
     * many items are in the queue.
     * */
    size_t (*length)(ts_queue_t *self);

    /* Returns a string representing the items in the queue. */
    char *(*repr)(ts_queue_t *self);

    /* Prints the queue representation to the stdout. */
    void (*display)(ts_queue_t *self);
};

/* Adds a new item to the back of the queue. */
extern int ts_queue_enqueue(ts_queue_t *queue, ts_generic_t value);

/* Returns the item in the front of the queue, removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern ts_generic_t ts_queue_dequeue(ts_queue_t *queue);

/* Returns the item in the front of the queue, without removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern ts_generic_t ts_queue_peek(ts_queue_t *queue);

/* Returns the length of the queue, which represents how
 * many items are in the queue.
 * */
extern size_t ts_queue_length(ts_queue_t *queue);

/* Returns a string representing the items in the queue. */
extern char *ts_queue_repr(ts_queue_t *queue);

/* Prints the queue representation to the stdout. */
extern void ts_queue_display(ts_queue_t *self);

/* Creates and returns a new queue. */
extern ts_queue_t *ts_new_queue();

/* Deallocates the memory used in the queue. */
extern void ts_queue_free(ts_queue_t **queue);

#endif
