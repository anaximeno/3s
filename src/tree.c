#include "../include/3s/tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct s3_tree_node* s3_tree_node;


static s3_tree_node s3_tree_node_new(void)
{
    s3_tree_node node = (s3_tree_node) malloc(sizeof(struct s3_tree_node));

    if (node != NULL) {
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->value = NULL;
        node->position = ROOT;
        node->depth = 0;
    }

    return node;
}


static int insert_value_in_btree(s3_tree_t* tree, s3_tree_node* root, s3_value_t value,
                                        s3_tree_node_pos position, s3_tree_node parent)
{
#define DEPTH(PARENT_NODE) (PARENT_NODE != NULL ? PARENT_NODE->depth + 1 : 0)
#define REP(TREE, STRAT) (TREE.on_repeated == SRAT)

    if (*root == NULL) {
        s3_tree_node node = s3_tree_node_new();

        if (node != NULL) {
            node->parent = parent;
            node->position = position;
            node->value = value;
            node->depth = DEPTH(parent);
            *root = node;
        } else
            goto return_error;

        return node->depth;
    } else {
        const cmp = s3_value_compare(value, (*root)->value);

        if (cmp == S3_VALUE_LESS || (cmp == S3_VALUE_EQUAL && REP(tree, APPEND_LEFT)))
            return insert_value_in_btree(tree, &(*root)->left, value, LEFT, *root);
        else if (cmp == S3_VALUE_GREATER || (cmp == S3_VALUE_EQUAL && REP(tree, APPEND_RIGTH)))
            return insert_value_in_btree(tree, &(*root)->right, value, RIGTH, *root);
        else if (cmp == S3_VALUE_DIFFERENT)
            return s3_tree_add(tree->next, value); // Add to another tree
        else /* IGNORE */ ;
    }

return_error:
    return S3_TREE_VALUE_NOT_ADDED;
}


extern int s3_tree_add(s3_tree_t* tree, s3_value_t value)
{
    if (tree->root == NULL && value != NULL)
        tree->type_of_value = value->type;
    return insert_value_in_btree(tree, &tree->root, value, LEFT, NULL);
}

extern b_tree* s3_tree_new(s3_tree_on_repeated on_repeated)
{
    b_tree* tree = (b_tree*) malloc(sizeof(b_tree));

    if (tree != NULL) {
        tree->root = NULL;
        tree->on_repeated = on_repeated;

        tree->add = &s3_tree_add;
    }

    return tree;
}


static void s3_tree_node_free(s3_tree_node* node)
{
    if (*node != NULL) {
        s3_tree_node_free(&(*node)->left);
        s3_tree_node_free(&(*node)->right);

        if ((*node)->value != NULL) {
            free((*node)->value);
            (*node)->value = NULL;
        }

        free(*node);
        *node = NULL;
    }

#ifdef _MAKE_ROBUST_CHECK
    assert(node == NULL);
#endif
}


extern void s3_tree_free(b_tree** tree)
{
    if (*tree != NULL) {
        if ((*tree)->next != NULL) {
            s3_tree_free(&(*tree)->next);
        }

        s3_tree_node_free(&(*tree)->root);


        free(*tree);
        *tree = NULL;
    }

#ifdef _MAKE_ROBUST_CHECK
    assert(*tree == NULL);
#endif
}
