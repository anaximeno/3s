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
        node->value = NULL;
        node->rel_pos = ROOT;
        node->level = 0;
    }

    return node;
}


static void insert_value_in_btree(_b_node* root, value_t value, b_node_pos pos,
                                        _b_node parent, b_node_rep_st rep_strategy)
{
    if (*root == NULL) {
        _b_node node = new_b_node();

        if (node != NULL) {
            node->parent = parent;
            node->rel_pos = pos;
            node->value = value;
            node->level = parent != NULL ? parent->level + 1 : 0;
        }

        *root = node;
    } else {
        const value_t r_val = (*root)->value;
        if (r_val < value || (r_val == value && rep_strategy == APPEND_LEFT))
            insert_value_in_btree(&(*root)->left, value, LEFT, *root, rep_strategy);
        else if (r_val > value || (r_val == value && rep_strategy == APPEND_RIGHT))
            insert_value_in_btree(&(*root)->right, value, RIGTH, *root, rep_strategy);
        else
            /* Repeated value, and rep_strategy is IGNORE. */
        ;
    }
}


static void add_value_to_b_tree(b_tree* self, value_t value)
{
    insert_value_in_btree(&self->root, value, ROOT, NULL, self->rep_strategy);
}


extern b_tree* new_btree(b_node_rep_st rep_strategy)
{
    b_tree* tree = (b_tree*) malloc(sizeof(b_tree));

    if (tree != NULL) {
        tree->root = NULL;
        tree->rep_strategy = rep_strategy;
        tree->add = &add_value_to_b_tree;
    }

    return tree;
}


static void free_btree_node(_b_node* node)
{
    if (*node != NULL) {
        free_btree_node(&(*node)->left);
        free_btree_node(&(*node)->right);
        free(*node);
        *node = NULL;
    }
}


extern void free_btree(b_tree** tree)
{
    if (*tree != NULL) {
        free_btree_node(&(*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}
