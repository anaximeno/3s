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

#ifndef _3S_LINKED_LIST_HEADER
#define _3S_LINKED_LIST_HEADER

#include "./core.h"

#include <stdlib.h>
#include <string.h>

/* Returned when searching for values on lists. */
#define S3_VALUE_NOT_FOUND -1

typedef struct s3_list_t s3_list_t;


/* Represents a unique node of the doubly-linked list. */
struct s3_linked_node {
    struct s3_linked_node* next;
    struct s3_linked_node* prev;
    s3_value_t value;
};


/* Represents the linked list as a whole. */
struct s3_list_t {
    struct s3_linked_node* head;
    struct s3_linked_node* tail;
    unsigned length;

    /* Add a new value to the front of the list. */
    void (*append_front) (s3_list_t* self, s3_value_t value);
    /* Add a new value to the back of the list. */
    void (*append_back) (s3_list_t* self, s3_value_t value);
    /* Returns the first index of the value on this list. */
    int (*index) (s3_list_t* self, s3_value_t value);
    /* Returns the value at the given index. Zero will be returned
     * by default for out of bound indexes. */
    s3_value_t (*get) (s3_list_t* self, unsigned index);
    /* Removed a value at the given index. */
    void (*remove_at_index) (s3_list_t* self, unsigned index);
    /* Removes all occorences of the value on the list. */
    void (*remove_all) (s3_list_t* self, s3_value_t value);
    /* Prints the list. */
    void (*display) (s3_list_t* self);
    /* Returns the string representation of this list.*/
    char* (*repr) (s3_list_t* self);
};

/* Used to add a new value to the back of the linked list. */
extern void s3_list_append_back(s3_list_t* list, s3_value_t value);

/* Used to add a new value to the front of the linked list. */
extern void s3_list_append_front(s3_list_t* list, s3_value_t value);

/* Returns the index of a value in the list.
 * If the value was not found the constant `S3_VALUE_NOT_FOUND` is
 * returned instead.
 * */
extern int s3_list_get_first_index(s3_list_t* list, s3_value_t value);


/* Returns the value at the given index. NULL will be returned
 * by default for out of bound indexes.
 * */
extern s3_value_t s3_list_get_value(s3_list_t* list, unsigned idx);

/* Removes the value at the given index. */
extern void s3_list_remove_at_index(s3_list_t* list, unsigned index);

/* Removes all occorences of the value on the list. */
extern void s3_list_remove_value(s3_list_t* list, s3_value_t value);

/* Returns a pointer new allocated linked list. */
extern s3_list_t* s3_new_list(void);

/* Used to free the allocated memory of a s3_list_t structure. */
extern void s3_list_free(s3_list_t** list);

/* Returns the string representation of a list. */
extern char* s3_list_repr(s3_list_t* list);

/* Prints a linked list. */
extern void s3_list_display(s3_list_t* list);

/* Generates a block with the algorithm to create the list representation.
 *
 * @params LIST, PREFIX, POSTFIX, SEP, PRINT_STRATEGY
 *
 * @param LIST - should be a pointer to a s3_list_t structure.
 * @param PREFIX - a string representing the prefix of the list, ususally "["
 * @param POSTFIX - a string representing the postfix of the list, ususally "]"
 * @param SEP - the string that is in between each item shown.
 * @param PRINT_STRATEGY - The strategy of the list printing algorithm. Must be FORWARD or BACKWARD.
 */
#define __LIST_REPR_ALGORITHM(LIST, PREFIX, POSTFIX, SEP, PRINT_STRATEGY) {\
    const unsigned __pfixex_len = strlen(PREFIX);\
    const unsigned __list_length = (LIST) != NULL ? LIST->length : 0;\
    const unsigned __sep_len = strlen(SEP) * (__list_length - 1);\
    size_t __speculative_size = __list_length * __VALUE_T_REPR_BUFFER_MAX_SIZE;\
    __speculative_size += __pfixex_len + __sep_len;\
    char* repr = (char*) calloc(__speculative_size, sizeof(char));\
    if (repr != NULL) {\
        strcat(repr, (PREFIX));\
        __PRINT_LIST_##PRINT_STRATEGY(LIST, SEP);\
        strcat(repr, POSTFIX);\
        repr = realloc(repr, strlen(repr) + 1);\
    }\
    return repr;\
}

#define __PRINT_LIST_FORWARD(LIST, SEP) {\
    for (unsigned i = 0 ; i < __list_length ; ++i) {\
        const s3_value_t value = LIST->get(LIST, i);\
        char* value_repr = value->repr(value);\
        strcat(repr, value_repr);\
        if (i + 1 != __list_length)\
            strcat(repr, SEP);\
        free(value_repr);\
    }\
}

#define __PRINT_LIST_BACKWARD(LIST, SEP) {\
    for (unsigned i = __list_length ; i > 0 ; --i) {\
        const s3_value_t value = LIST->get(LIST, i - 1);\
        char* value_repr = value->repr(value);\
        strcat(repr, value_repr);\
        if (i - 1 != 0)\
            strcat(repr, SEP);\
        free(value_repr);\
    }\
}

#endif /* _3S_LINKED_LIST_HEADER */
