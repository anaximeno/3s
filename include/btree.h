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

enum BinaryThreePrintOrder {
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
};

typedef struct binarytree b_tree;

typedef enum BinNodePosition                b_node_pos;
typedef enum BinNodeRepetitionStrategy      b_node_rep_st;
typedef enum BinaryThreePrintOrder          b_tree_print_ord;


/* Represents a unique node of the binary tree. */
struct _binary_node {
    struct _binary_node* parent;
    struct _binary_node* left;
    struct _binary_node* right;
    b_node_pos rel_pos;
    s3_value_t value;
    unsigned level;
};


/* Represents the binary tree as a whole. */
struct binarytree {
    struct _binary_node* root;
    b_node_rep_st rep_strategy;
    unsigned depth;

    /* Adds a new value to the binary tree. */
    void (*add) (b_tree* self, s3_value_t value);

    /* Searchs for the value on the tree and returns the level in
     * which it was firstly found. If the value is not inside the tree,
     * the constant `VALUE_NOT_FOUND` is returned.
     * */
    int (*search) (b_tree* self, s3_value_t value);

    /* Searchs for a value, returning the level it was first found, after
     * the given level.
     * */
    int (*search_after_level) (b_tree* self, s3_value_t value, unsigned level);

    /* Removes the given value completely from the b_tree.
     * If the repetition strategy chosen was APPEND_(LEFT/RIGTH),
     * other repetitions will also be removed.
     * */
    void (*remove) (b_tree* self, s3_value_t value);

    /* Removes the given value if it is in the given level of the tree. */
    void (*remove_at_level) (b_tree* self, s3_value_t value, unsigned level);

    /* Prints the binary tree in the order determined by the param ord. */
    void (*print) (b_tree_print_ord ord);

    /* Balances the binary tree using the AVL tree balancing algorithm. */
    void (*balance) (b_tree* self);
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
