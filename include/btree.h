#ifndef _3S_B_TREE_HEADER
#define _3S_B_TREE_HEADER

#include "./core.h"

#include <stdlib.h>
#include <stdbool.h>


enum BinNodePosition {
    LEFT,
    RIGTH,
    ROOT
};


enum BinNodeRepetitionStrategy {
    APPEND_LEFT,
    APPEND_RIGHT,
    IGNORE
};

typedef struct binarytree b_tree;
typedef enum BinNodePosition b_node_pos;
typedef enum BinNodeRepetitionStrategy b_node_rep_st;


/* Represents a unique node of the binary tree. */
struct _binary_node {
    struct _binary_node* parent;
    struct _binary_node* left;
    struct _binary_node* right;
    b_node_pos relative_positioning;
    value_t value;
    unsigned level;
};


/* Represents the binary tree as a whole. */
struct binarytree {
    struct _binary_node* root;
    b_node_rep_st rep_strategy;
    unsigned depth;

    void (*add) (b_tree* self, value_t value);
};


/* Returns a pointer new allocated binary tree.
 * The parameter rep_strategy may be used to determine
 * what to do when a value is added more than once to the
 * binary b tree.
 * */
extern b_tree* new_btree(b_node_rep_st rep_strategy);

/* Used to free the allocated memory of a binary tree structure. */
extern void free_btree(b_tree** tree);

#endif /* _3S_B_TREE_HEADER */
