#ifndef _3S_B_TREE_HEADER
#define _3S_B_TREE_HEADER

#include "./core.h"

#include <stdlib.h>


typedef struct binarytree b_tree;


/* Represents a unique node of the binary tree. */
struct _binary_node {
    struct _binary_node* parent;
    struct _binary_node* left;
    struct _binary_node* right;
    char* relative_positioning;
    unsigned depth;
    value_t value;
};


/* Represents the binary tree as a whole. */
struct binarytree {
    struct _binary_node* root;
    unsigned depth;

    void (*add) (struct binarytree* self, value_t value);
};


/* Returns a pointer new allocated binary tree. */
extern b_tree* new_btree(void);

/* Used to free the allocated memory of a binary tree structure. */
extern void free_btree(b_tree** tree);

#endif /* _3S_B_TREE_HEADER */