#ifndef _3S_LINKED_LIST_HEADER
#define _3S_LINKED_LIST_HEADER

#include "./core.h"

#include <stdlib.h>
#include <string.h>


typedef struct s3_linked_list s3_linked_list;


/* Represents a unique node of the doubly-linked list. */
struct s3_linked_node {
    struct s3_linked_node* next;
    struct s3_linked_node* prev;
    s3_value_t value;
};


/* Represents the linked list as a whole. */
struct s3_linked_list {
    struct s3_linked_node* head;
    struct s3_linked_node* tail;
    unsigned length;

    /* Add a new value to the front of the list. */
    void (*append_front) (s3_linked_list* self, s3_value_t value);
    /* Add a new value to the back of the list. */
    void (*append_back) (s3_linked_list* self, s3_value_t value);
    /* Returns the first index of the value on this list. */
    int (*index) (s3_linked_list* self, s3_value_t value);
    /* Returns the value at the given index. Zero will be returned
     * by default for out of bound indexes. */
    s3_value_t (*get) (s3_linked_list* self, unsigned index);
    /* Removed a value at the given index. */
    void (*remove_at_index) (s3_linked_list* self, unsigned index);
    /* Removes all occorences of the value on the list. */
    void (*remove_all) (s3_linked_list* self, s3_value_t value);
    /* Prints the list. */
    void (*display) (s3_linked_list* self);
    /* Returns the string representation of this list.*/
    char* (*repr) (s3_linked_list* self);
};


/* Returns a pointer new allocated linked list. */
extern s3_linked_list* new_list(void);

/* Used to free the allocated memory of a s3_linked_list structure. */
extern void s3_list_free(s3_linked_list** list);

/* Generates a block with the algorithm to create the list representation.
 *
 * @params LIST, PREFIX, POSTFIX, SEP, PRINT_STRATEGY
 *
 * @param LIST - should be a pointer to a s3_linked_list structure.
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
