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

#ifndef _3S_TREE_HEADER
#define _3S_TREE_HEADER

#include "./core.h"

#include <stdlib.h>
#include <stdbool.h>

/* This is returned when a value could not be added to the tree. */
#define TS_TREE_VALUE_NOT_ADDED -1

/* Represents the relative position of a tree node. */
typedef enum ts_tree_node_position
{
    TS_TREE_NODE_LEFT,
    TS_TREE_NODE_ROOT,
    TS_TREE_NODE_RIGTH
} ts_tree_node_position;

/* Represents what should be done when one value is inserted
 * more than once inside a tree.
 * */
typedef enum ts_tree_on_dup_value_strategy
{
    TS_TREE_APPEND_LEFT,
    TS_TREE_APPEND_RIGHT,
    TS_TREE_IGNORE
} ts_tree_on_dup_value_strategy;

/* Represents the order in which this tree should be printed. */
typedef enum ts_tree_printing_order
{
    TS_TREE_IN_ORDER,
    TS_TREE_PRE_ORDER,
    TS_TREE_POST_ORDER
} ts_tree_printing_order;

typedef struct ts_tree_t ts_tree_t;

/* Represents a unique node of the binary tree. */
struct ts_tree_node
{
    /* The parent node. */
    struct ts_tree_node *parent;
    /* The left node. */
    struct ts_tree_node *left;
    /* The right node. */
    struct ts_tree_node *right;
    /* The relative position of this node in
     * relation with its parent node. This can
     * have the values: LEFT, RIGTH, and ROOT
     * */
    ts_tree_node_position position;
    /* The value stored in this node. */
    ts_generic_t value;
    /* The depth of this node. It begins on zero,
     * on the root node, and then is incremented accordingly
     * to the parent's depth.
     * */
    size_t depth;
};

/* Represents the binary tree as a whole. */
struct ts_tree_t
{
    /* Represents the root node of this tree. */
    struct ts_tree_node *root;
    /* This will hold another tree if necessary. In case of adding values
     * of different types than the one in the root node, the value will be
     * stored on a side tree.
     * */
    ts_tree_t *next;
    /* Anotates what should be the default procedure when inserting a value
     * more than once. It can be: APPEND_LEFT, APPEND_RIGHT, and IGNORE.
     * */
    ts_tree_on_dup_value_strategy on_dup_value_strat;
    /* This is the full depth of this tree. It stores the depth of the most deep node.
     * */
    size_t full_depth;
    /* Represents the type of value that is being stored in this particular instance
     * of this structure.
     * */
    ts_types type_of_value;

    /* Adds a new value to the binary tree. If the value was added successfully
     * it returns the depth of the value, else the constant TS_TREE_VALUE_NOT_ADDED.
     * */
    int (*add)(ts_tree_t *self, ts_generic_t value);

    /* Searchs for the value on the tree and returns the depth in
     * which it was firstly found. If the value is not inside the tree,
     * the constant `TS_TREE_VALUE_NOT_ADDED` is returned.
     * */
    int (*search)(ts_tree_t *self, ts_generic_t value);

    /* Removes the given value completely from the ts_tree_t.
     * If the repetition strategy chosen was APPEND_(LEFT/RIGTH),
     * other repetitions will also be removed.
     * */
    void (*remove)(ts_tree_t *self, ts_generic_t value);

    /* Returns the string representation of this tree, organized in the give order. */
    char *(*repr)(ts_tree_t *self, ts_tree_printing_order order);

    /* Prints the binary tree in the order determined by the param ord. */
    void (*display)(ts_tree_t *self, ts_tree_printing_order order);

    /* Balances the binary tree using the AVL tree balancing algorithm. */
    void (*balance)(ts_tree_t *self);
};

/* Adds a new value to the binary tree. If the value was added successfully
 * it returns the depth of the value, else the constant TS_TREE_VALUE_NOT_ADDED.
 * */
extern int ts_tree_add(ts_tree_t *tree, ts_generic_t value);

/* Searchs for the value on the tree and returns the depth in
 * which it was firstly found. If the value is not inside the tree,
 * the constant `TS_TREE_VALUE_NOT_ADDED` is returned.
 * */
extern int ts_tree_search(ts_tree_t *tree, ts_generic_t value);

/* Removes the given value completely from the ts_tree_t.
 * If the repetition strategy chosen was APPEND_(LEFT/RIGTH),
 * other repetitions will also be removed.
 * */
extern void ts_tree_remove(ts_tree_t *tree, ts_generic_t value);

/* Returns the string representation of this tree, organized in the give order. */
extern char *ts_tree_repr(ts_tree_t *tree, ts_tree_printing_order order);

/* Prints the binary tree in the order determined by the param ord. */
extern void ts_tree_display(ts_tree_t *tree, ts_tree_printing_order order);

/* Balances the binary tree using the AVL tree balancing algorithm. */
extern void ts_tree_balance(ts_tree_t *tree);

/* Returns a pointer new allocated binary tree.
 * The parameter on_dup_value_strat is used to determine
 * what to do when a value is added more than once to the
 * tree.
 * */
extern ts_tree_t *ts_tree_new(ts_tree_on_dup_value_strategy on_dup_value_strat);

/* Used to free the allocated memory of a binary tree structure. */
extern void ts_tree_free(ts_tree_t **tree);

#endif /* _3S_TREE_HEADER */
