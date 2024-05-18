/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (c) 2022 Anaxímeno Brito                                                *
 *                                                                                   *
 * Permission is hereby granted, free of charge, to any person obtaining a copy      *
 * of this software and associated documentation files (the "Software"), to deal     *
 * in the Software without restriction, including without limitation the rights      *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell         *
 * copies of the Software, and to permit persons to whom the Software is             *
 * furnished to do so, subject to the following conditions:                          *
 *                                                                                   *
 * The above copyright notice and this permission notice shall be included in all    *
 * copies or substantial portions of the Software.                                   *
 *                                                                                   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,          *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE       *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER            *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,     *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     *
 * SOFTWARE.                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../include/3s/tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct s3_tree_node *s3_tree_node;

static s3_tree_node s3_tree_node_new(void)
{
    s3_tree_node node = (s3_tree_node)malloc(sizeof(struct s3_tree_node));

    if (node != NULL)
    {
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->value = NULL;
        node->position = ROOT;
        node->depth = 0;
    }

    return node;
}

static int insert_value_in_btree(s3_tree_t *tree, s3_tree_node *root, s3_value_t value,
                                 s3_tree_node_position position, s3_tree_node parent)
{
#define DEPTH(PARENT_NODE) (PARENT_NODE != NULL ? PARENT_NODE->depth + 1 : 0)
#define REP(TREE, STRAT) (TREE.on_repeated == SRAT)

    if (*root == NULL)
    {
        s3_tree_node node = s3_tree_node_new();

        if (node != NULL)
        {
            node->parent = parent;
            node->position = position;
            node->value = value;
            node->depth = DEPTH(parent);
            *root = node;
        }
        else
            goto return_error;

        return node->depth;
    }
    else
    {
        const cmp = s3_value_compare(value, (*root)->value);

        if (cmp == S3_VALUE_LESS || (cmp == S3_VALUE_EQUAL && REP(tree, APPEND_LEFT)))
            return insert_value_in_btree(tree, &(*root)->left, value, LEFT, *root);
        else if (cmp == S3_VALUE_GREATER || (cmp == S3_VALUE_EQUAL && REP(tree, APPEND_RIGTH)))
            return insert_value_in_btree(tree, &(*root)->right, value, RIGTH, *root);
        else if (cmp == S3_VALUE_DIFFERENT)
            return s3_tree_add(tree->next, value); // Add to another tree
        else                                       /* IGNORE */
            ;
    }

return_error:
    return S3_TREE_VALUE_NOT_ADDED;
}

extern int s3_tree_add(s3_tree_t *tree, s3_value_t value)
{
    if (tree->root == NULL && value != NULL)
        tree->type_of_value = value->type;
    return insert_value_in_btree(tree, &tree->root, value, LEFT, NULL);
}

extern s3_tree_t *s3_tree_new(s3_tree_on_repeated_enum on_repeated)
{
    s3_tree_t *tree = (s3_tree_t *)malloc(sizeof(s3_tree_t));

    if (tree != NULL)
    {
        tree->root = NULL;
        tree->on_repeated = on_repeated;
        tree->add = &s3_tree_add;
    }

    return tree;
}

static void s3_tree_node_free(s3_tree_node *node)
{
    if (*node != NULL)
    {
        s3_tree_node_free(&(*node)->left);
        s3_tree_node_free(&(*node)->right);

        if ((*node)->value != NULL)
        {
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

extern void s3_tree_free(s3_tree_t **tree)
{
    if (*tree != NULL)
    {
        if ((*tree)->next != NULL)
        {
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
