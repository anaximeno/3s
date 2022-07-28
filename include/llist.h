#ifndef _3S_LINKED_LIST_HEADER
#define _3S_LINKED_LIST_HEADER

#include "./core.h"

#include <stdlib.h>


typedef struct linkedlist l_list;


/* Represents a unique node of the doubly-linked list. */
struct _linked_node {
    struct _linked_node* next;
    struct _linked_node* prev;
    value_t value;
};


/* Represents the linked list as a whole. */
struct linkedlist {
    struct _linked_node* head;
    struct _linked_node* tail;
    unsigned length;

    /* Add a new value to the list. */
    void (*add) (l_list* self, value_t value);
    /* Returns the first index of the value on this list. */
    int (*index) (l_list* self, value_t value);
    /* Returns the value at the given index. Zero will be returned
     * by default for out of bound indexes. */
    value_t (*get) (l_list* self, unsigned index);
};


/* Returns a pointer new allocated linked list. */
extern l_list* new_list(void);

/* Used to free the allocated memory of a linkedlist structure. */
extern void free_list(l_list** list);

#endif /* _3S_LINKED_LIST_HEADER */