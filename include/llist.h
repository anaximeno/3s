#ifndef _3S_LINKED_LIST_HEADER
#define _3S_LINKED_LIST_HEADER

#include "./core.h"

#include <stdlib.h>


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
extern void free_list(s3_linked_list** list);

#endif /* _3S_LINKED_LIST_HEADER */
