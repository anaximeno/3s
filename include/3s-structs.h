#ifndef _3S_STRUCTS_HEADER
#define _3S_STRUCTS_HEADER

#include <stdlib.h>

/* General type of the values on the
 * trees and linked lists.
 * */
typedef int value_t;


/* Represents a unique node of the linked lists. */
struct _linked_node {
    struct _linked_node* next;
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

#endif /* 3S_STRUCTS_HEADER */