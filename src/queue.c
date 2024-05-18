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
#include "../include/3s/queue.h"
#include "../include/3s/llist.h"

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

/* Adds a new item to the back of the queue. */
extern int s3_queue_enqueue(s3_queue_t *queue, s3_value_t value)
{
    if (queue != NULL)
    {
        /* Try to create a new list, if not created previously. */
        if (queue->list == NULL)
        {
            /* Be aware that the function s3_new_list could still return NULL,
             * if there's no available space.
             * */
            queue->list = s3_new_list();
            queue->size = 0;
        }

        /* If the list was or could be allocated. */
        if (queue->list != NULL)
        {
            queue->list->append_back(queue->list, value);
            queue->size += 1;
#ifdef _MAKE_ROBUST_CHECK
            assert(queue->size == queue->list->length);
#endif /* _MAKE_ROBUST_CHECK */
            return 0;
        }
    }

    return 1;
}

/* Returns the item in the front of the queue, removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern s3_value_t s3_queue_dequeue(s3_queue_t *queue)
{
    if (queue != NULL)
    {
        if (queue->list != NULL && queue->list->length > 0)
        {
            s3_value_t dequeued = queue->list->get(queue->list, 0);
            s3_value_t value = (s3_value_t)malloc(sizeof(struct s3_value_t));

            /* Copy bytes from the value dequeued to the one that will be returned. */
            memcpy(value, dequeued, sizeof(struct s3_value_t));

            queue->list->remove_at_index(queue->list, 0);
            queue->size -= 1;
#ifdef _MAKE_ROBUST_CHECK
            assert(queue->size == queue->list->length);
#endif /* _MAKE_ROBUST_CHECK */
            return value;
        }
    }

    return NULL;
}

/* Returns the item in the front of the queue, without removing it from the queue.
 * If no values are found in the queue, then it returns NULL by default.
 * */
extern s3_value_t s3_queue_peek(s3_queue_t *queue)
{
    if (queue != NULL && queue->list != NULL && queue->list->length > 0)
        return queue->list->get(queue->list, 0);
    return NULL;
}

/* Returns the length of the queue, which represents how
 * many items are in the queue.
 * */
extern size_t s3_queue_length(s3_queue_t *queue)
{
    if (queue != NULL)
        return queue->size;
    return 0;
}

/* Returns a string representing the items in the queue. */
extern char *s3_queue_repr(s3_queue_t *queue)
    S3_LIST_REPR_ALGORITHM(
        queue->list,
        "<[",
        "]",
        " | ",
        FORWARD);

/* Prints the queue representation to the stdout. */
extern void s3_queue_display(s3_queue_t *self)
{
    char *repr = s3_queue_repr(self);
    printf("%s", repr);
    free(repr);
}

/* Creates and returns a new queue. */
extern s3_queue_t *s3_new_queue()
{
    s3_queue_t *queue = (s3_queue_t *)malloc(sizeof(s3_queue_t));

    if (queue != NULL)
    {
        queue->size = 0;
        queue->list = s3_new_list();

        /* Associated functions. */
        queue->enqueue = &s3_queue_enqueue;
        queue->dequeue = &s3_queue_dequeue;
        queue->peek = &s3_queue_peek;
        queue->length = &s3_queue_length;
        queue->repr = &s3_queue_repr;
        queue->display = &s3_queue_display;
    }

    return queue;
}

extern void s3_queue_free(s3_queue_t **queue)
{
    if (*queue != NULL)
    {
        s3_list_free(&(*queue)->list);
        free(*queue);
        *queue = NULL;
    }
}
