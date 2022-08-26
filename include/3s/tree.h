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
#define S3_TREE_VALUE_NOT_ADDED -1

/* Represents the relative position of a tree node. */
typedef enum s3_tree_node_pos {
    LEFT, RIGTH, ROOT
} s3_tree_node_pos;


/* Represents what should be done when one value is inserted
 * more than once inside a tree.
 * */
typedef enum s3_tree_on_repeated {
    APPEND_LEFT,
    APPEND_RIGHT,
    IGNORE
} s3_tree_on_repeated;

/* Represents the order in which this tree should be printed. */
typedef enum s3_tree_printing_order {
    IN_ORDER, PRE_ORDER, POST_ORDER
} s3_tree_printing_order;

typedef struct s3_tree_t s3_tree_t;

/* Represents a unique node of the binary tree. */
struct s3_tree_node {
    /* The parent node. */
    struct s3_tree_node* parent;
    /* The left node. */
    struct s3_tree_node* left;
    /* The right node. */
    struct s3_tree_node* right;
    /* The relative position of this node in
     * relation with its parent node. This can
     * have the values: LEFT, RIGTH, and ROOT
     * */
    s3_tree_node_pos position;
    /* The value stored in this node. */
    s3_value_t value;
    /* The depth of this node. It begins on zero,
     * on the root node, and then is incremented accordingly
     * to the parent's depth.
     * */
    size_t depth;
};

/* Represents the binary tree as a whole. */
struct s3_tree_t {
    /* Represents the root node of this tree. */
    struct s3_tree_node* root;
    /* This will hold another tree if necessary. In case of adding values
     * of different types than the one in the root node, the value will be
     * stored on a side tree.
     * */
    s3_tree_t* next;
    /* Anotates what should be the default procedure when inserting a value
     * more than once. It can be: APPEND_LEFT, APPEND_RIGHT, and IGNORE.
     * */
    s3_tree_on_repeated on_repeated;
    /* This is the full depth of this tree. It stores the depth of the most deep node.
     * */
    size_t full_depth;
    /* Represents the type of value that is being stored in this particular instance
     * of this structure.
     * */
    s3_value_types type_of_value;

    /* Adds a new value to the binary tree. If the value was added successfully
     * it returns the depth of the value, else the constant S3_TREE_VALUE_NOT_ADDED.
     * */
    int (*add) (s3_tree_t* self, s3_value_t value);

    /* Searchs for the value on the tree and returns the depth in
     * which it was firstly found. If the value is not inside the tree,
     * the constant `S3_TREE_VALUE_NOT_ADDED` is returned.
     * */
    int (*search) (s3_tree_t* self, s3_value_t value);

    /* Removes the given value completely from the s3_tree_t.
     * If the repetition strategy chosen was APPEND_(LEFT/RIGTH),
     * other repetitions will also be removed.
     * */
    void (*remove) (s3_tree_t* self, s3_value_t value);

    /* Returns the string representation of this tree, organized in the give order. */
    char* (*repr) (s3_tree_t* self, s3_tree_printing_order order);

    /* Prints the binary tree in the order determined by the param ord. */
    void (*display) (s3_tree_t* self, s3_tree_printing_order order);

    /* Balances the binary tree using the AVL tree balancing algorithm. */
    void (*balance) (s3_tree_t* self);
};

/* Adds a new value to the binary tree. If the value was added successfully
 * it returns the depth of the value, else the constant S3_TREE_VALUE_NOT_ADDED.
 * */
extern int s3_tree_add(s3_tree_t* tree, s3_value_t value);

/* Searchs for the value on the tree and returns the depth in
 * which it was firstly found. If the value is not inside the tree,
 * the constant `S3_TREE_VALUE_NOT_ADDED` is returned.
 * */
extern int s3_tree_search(s3_tree_t* tree, s3_value_t value);

/* Removes the given value completely from the s3_tree_t.
 * If the repetition strategy chosen was APPEND_(LEFT/RIGTH),
 * other repetitions will also be removed.
 * */
extern void s3_tree_remove(s3_tree_t* tree, s3_value_t value);

/* Returns the string representation of this tree, organized in the give order. */
extern char* s3_tree_repr(s3_tree_t* tree, s3_tree_printing_order order);

/* Prints the binary tree in the order determined by the param ord. */
extern void s3_tree_display(s3_tree_t* tree, s3_tree_printing_order order);

/* Balances the binary tree using the AVL tree balancing algorithm. */
extern void s3_tree_balance(s3_tree_t* tree);

/* Returns a pointer new allocated binary tree.
 * The parameter on_repeated is used to determine
 * what to do when a value is added more than once to the
 * tree.
 * */
extern s3_tree_t* s3_tree_new(s3_tree_on_repeated on_repeated);

/* Used to free the allocated memory of a binary tree structure. */
extern void s3_tree_free(s3_tree_t** tree);

#endif /* _3S_TREE_HEADER */
