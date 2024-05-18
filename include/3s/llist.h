/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (c) 2022-2024 Anaxímeno Brito                                                *
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

#ifndef _3S_LINKED_LIST_HEADER
#define _3S_LINKED_LIST_HEADER

#include "./core.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Returned when searching for values on lists. */
#define TS_NOT_FOUND -1

typedef struct ts_list_t ts_list_t;

/* Represents a unique node of the doubly-linked list. */
struct ts_linked_node
{
    struct ts_linked_node *next;
    struct ts_linked_node *prev;
    ts_generic_t value;
};

/* Represents the linked list as a whole. */
struct ts_list_t
{
    struct ts_linked_node *head;
    struct ts_linked_node *tail;
    unsigned length;

    /* Add a new value to the front of the list. */
    void (*append_front)(ts_list_t *self, ts_generic_t value);
    /* Add a new value to the back of the list. */
    void (*append_back)(ts_list_t *self, ts_generic_t value);
    /* Returns the first index of the value on this list. */
    int (*index)(ts_list_t *self, ts_generic_t value);
    /* Returns the value at the given index. Zero will be returned
     * by default for out of bound indexes. */
    ts_generic_t (*get)(ts_list_t *self, unsigned index);
    /* Removed a value at the given index. */
    void (*remove_at_index)(ts_list_t *self, unsigned index);
    /* Removes all occorences of the value on the list. */
    void (*remove_all)(ts_list_t *self, ts_generic_t value);
    /* Prints the list. */
    void (*display)(ts_list_t *self);
    /* Returns the string representation of this list.*/
    char *(*repr)(ts_list_t *self);
};

/* Used to add a new value to the back of the linked list. */
extern void ts_list_append_back(ts_list_t *list, ts_generic_t value);

/* Used to add a new value to the front of the linked list. */
extern void ts_list_append_front(ts_list_t *list, ts_generic_t value);

/* Returns the index of a value in the list.
 * If the value was not found the constant `TS_NOT_FOUND` is
 * returned instead.
 * */
extern int ts_list_get_first_index(ts_list_t *list, ts_generic_t value);

/* Returns the value at the given index. NULL will be returned
 * by default for out of bound indexes.
 * */
extern ts_generic_t ts_list_get_value(ts_list_t *list, unsigned idx);

/* Removes the value at the given index. */
extern void ts_list_remove_at_index(ts_list_t *list, unsigned index);

/* Removes all occorences of the value on the list. */
extern void ts_list_remove_value(ts_list_t *list, ts_generic_t value);

/* Returns a pointer new allocated linked list. */
extern ts_list_t *ts_new_list(void);

/* Used to free the allocated memory of a ts_list_t structure. */
extern void ts_list_free(ts_list_t **list);

/* Returns the string representation of a list. */
extern char *ts_list_repr(ts_list_t *list);

/* Prints a linked list. */
extern void ts_list_display(ts_list_t *list);

/* Generates a block with the algorithm to create the list representation.
 *
 * @params LIST, PREFIX, POSTFIX, SEP, PRINT_STRATEGY
 *
 * @param LIST - should be a pointer to a ts_list_t structure.
 * @param PREFIX - a string representing the prefix of the list, ususally "["
 * @param POSTFIX - a string representing the postfix of the list, ususally "]"
 * @param SEP - the string that is in between each item shown.
 * @param PRINT_STRATEGY - The strategy of the list printing algorithm. Must be FORWARD or BACKWARD.
 */
#define TS_LIST_REPR_ALGORITHM(LIST, PREFIX, POSTFIX, SEP, PRINT_STRATEGY)     \
    {                                                                          \
        const unsigned pfx = strlen(PREFIX);                                   \
        const unsigned llength = (LIST) != NULL ? LIST->length : 0;            \
        const unsigned spsize = llength > 0 ? strlen(SEP) * (llength - 1) : 0; \
        const size_t size = llength * TS_MAX_REPR_STR_BUF_SIZE + pfx + spsize; \
                                                                               \
        char *repr = (char *)calloc(size, sizeof(char));                       \
                                                                               \
        if (repr != NULL)                                                      \
        {                                                                      \
            strcat(repr, (PREFIX));                                            \
            TS_PRINT_LIST_##PRINT_STRATEGY(LIST, SEP);                         \
            strcat(repr, POSTFIX);                                             \
            repr = realloc(repr, strlen(repr) + 1);                            \
        }                                                                      \
                                                                               \
        return repr;                                                           \
    }

#define TS_PRINT_LIST_FORWARD(LIST, SEP)                   \
    {                                                      \
        for (unsigned i = 0; i < llength; ++i)             \
        {                                                  \
            const ts_generic_t value = LIST->get(LIST, i); \
            char *value_repr = value->repr(value);         \
            strcat(repr, value_repr);                      \
            if (i + 1 != llength)                          \
                strcat(repr, SEP);                         \
            free(value_repr);                              \
        }                                                  \
    }

#define TS_PRINT_LIST_BACKWARD(LIST, SEP)                      \
    {                                                          \
        for (unsigned i = llength; i > 0; --i)                 \
        {                                                      \
            const ts_generic_t value = LIST->get(LIST, i - 1); \
            char *value_repr = value->repr(value);             \
            strcat(repr, value_repr);                          \
            if (i - 1 != 0)                                    \
                strcat(repr, SEP);                             \
            free(value_repr);                                  \
        }                                                      \
    }

#endif /* _3S_LINKED_LIST_HEADER */
