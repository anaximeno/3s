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

typedef struct ts_tree_node *ts_tree_node;

static ts_tree_node ts_tree_node_new(void)
{
    ts_tree_node node = (ts_tree_node)malloc(sizeof(struct ts_tree_node));

    if (node != NULL)
    {
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->value = NULL;
        node->position = TS_TREE_NODE_ROOT;
        node->depth = 0;
    }

    return node;
}

static int insert_value_in_btree(ts_tree_t *tree, ts_tree_node *root, ts_generic_t value,
                                 ts_tree_node_position position, ts_tree_node parent)
{
#define DEPTH(PARENT_NODE) (PARENT_NODE != NULL ? PARENT_NODE->depth + 1 : 0)
#define REP(TREE, STRAT) (TREE.on_dup_value_strat == STRAT)

    if (*root == NULL)
    {
        ts_tree_node node = ts_tree_node_new();

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
        const cmp = ts_compare(value, (*root)->value);

        if (cmp == TS_LESS || (cmp == TS_EQUAL && tree->on_dup_value_strat == TS_TREE_APPEND_LEFT))
            return insert_value_in_btree(tree, &(*root)->left, value, TS_TREE_NODE_LEFT, *root);
        else if (cmp == TS_GREATER || (cmp == TS_EQUAL && tree->on_dup_value_strat == TS_TREE_APPEND_RIGHT))
            return insert_value_in_btree(tree, &(*root)->right, value, TS_TREE_NODE_RIGTH, *root);
        else if (cmp == TS_DIFFERENT)
            return ts_tree_add(tree->next, value); // Add to another tree
        else
            // IGNORE
            ;
    }

return_error:
    return TS_TREE_VALUE_NOT_ADDED;
}

extern int ts_tree_add(ts_tree_t *tree, ts_generic_t value)
{
    if (tree->root == NULL && value != NULL)
        tree->type_of_value = value->type;
    return insert_value_in_btree(tree, &tree->root, value, TS_TREE_NODE_LEFT, NULL);
}

extern ts_tree_t *ts_tree_new(ts_tree_on_dup_value_strategy on_dup_value_strat)
{
    ts_tree_t *tree = (ts_tree_t *)malloc(sizeof(ts_tree_t));

    if (tree != NULL)
    {
        tree->root = NULL;
        tree->on_dup_value_strat = on_dup_value_strat;
        tree->add = &ts_tree_add;
    }

    return tree;
}

static void ts_tree_node_free(ts_tree_node *node)
{
    if (*node != NULL)
    {
        ts_tree_node_free(&(*node)->left);
        ts_tree_node_free(&(*node)->right);

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

extern void ts_tree_free(ts_tree_t **tree)
{
    if (*tree != NULL)
    {
        if ((*tree)->next != NULL)
        {
            ts_tree_free(&(*tree)->next);
        }

        ts_tree_node_free(&(*tree)->root);

        free(*tree);
        *tree = NULL;
    }

#ifdef _MAKE_ROBUST_CHECK
    assert(*tree == NULL);
#endif
}
