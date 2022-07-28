#ifndef _3S_STRUCTS_HEADER
#define _3S_STRUCTS_HEADER

#include <stdlib.h>

#define VALUE_NOT_FOUND -1

/* General type of the values on the
 * trees and linked lists.
 * */
typedef int value_t;


/* Represents a unique node of the doubly-linked list. */
struct _linked_node {
    struct _linked_node* next;
    struct _linked_node* prev;
    value_t value;
};


/* Represents a unique node of the binary tree. */
struct _binary_node {
    struct _binary_node* parent;
    struct _binary_node* left;
    struct _binary_node* right;
    char* relative_positioning;
    unsigned depth;
    value_t value;
};


/* Represents the linked list as a whole. */
struct linkedlist {
    struct _linked_node* head;
    struct _linked_node* tail;
    unsigned length;

    /* Add a new value to the list. */
    void (*add) (struct linkedlist* this, value_t value);
    /* Returns the first index of the value on this list. */
    int (*index) (struct linkedlist* this, value_t value);
    /* Returns the value at the given index. Zero will be returned
     * by default for out of bound indexes. */
    value_t (*get) (struct linkedlist* this, unsigned index);
};


/* Represents the binary tree as a whole. */
struct binarytree {
    struct _binary_node* root;
    unsigned depth;

    void (*add) (struct binarytree* this, value_t value);
};

typedef struct linkedlist l_list;
typedef struct binarytree b_tree;


/* Returns a pointer new allocated linked list. */
extern l_list* new_list(void);

/* Returns a pointer new allocated binary tree. */
extern b_tree* new_btree(void);


/* Used to free the allocated memory of a linkedlist structure. */
extern void free_list(l_list** list);

/* Used to free the allocated memory of a binary tree structure. */
extern void free_btree(b_tree** tree);

#endif /* 3S_STRUCTS_HEADER */