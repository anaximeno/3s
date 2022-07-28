#include "../include/btree.h" 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _binary_node* _b_node;


static _b_node new_b_node(void)
{
    _b_node node = (_b_node) malloc(sizeof(struct _binary_node));

    if (node != NULL) {
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->relative_positioning = ROOT;
        node->value = 0;
        node->level = 0;
    }

    return node;
}

static void insert_value_in_btree(_b_node* root, value_t value, b_node_pos pos,
                                        _b_node* parent, b_node_rep_st rep_strat)
{
    if (*root == NULL) {
        _b_node node = new_b_node();
        
        if (node != NULL) {
            node->parent = parent;
            node->relative_positioning = pos;
            node->value = value;
            node->level = parent != NULL ? parent->level + 1 : 0;
        }
    } else {
        const value_t r_val = (*root)->value;
        if (r_val < value || (r_val == value && rep_strat == APPEND_LEFT))
            insert_value_in_btree(&(*root)->left, LEFT, *root, rep_strat);
        else if (r_val > value || (r_val == value && rep_strat == APPEND_RIGTH))
            insert_value_in_btree(&(*root)->right, RIGTH, *root, rep_strat);
        else
            /* Repeated value, and rep_strat is IGNORE. */
    }
}


static void add_value_to_b_tree(b_tree* self, value_t value)
{
    insert_value_in_btree(&self->root, value, ROOT, NULL, self->repetition_strat);
}


extern b_tree* new_btree(b_node_rep_st rep_strategy)
{
    b_tree* tree = (b_tree*) malloc(sizeof(b_tree));

    if (tree != NULL) {
        tree->root = NULL;
        tree->repetition_strat = rep_strategy;
        tree->add = &add_value_to_b_tree;
    }

    return tree;
}
