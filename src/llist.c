#include "../include/core.h"
#include "../include/llist.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct s3_linked_node* s3_linked_node;


/* Creates a new linked node. */
static s3_linked_node new_linked_node(void)
{
    s3_linked_node node = (s3_linked_node) malloc(sizeof(struct s3_linked_node));

    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->value = NULL;
    }

    return node;
}


/* Used to add a new value to the back of the linked list. */
static void append_to_the_back_of_the_list(s3_list_t* self, s3_value_t value)
{
    if (self != NULL) {
        if (self->head == NULL) {
            s3_linked_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                self->head = head;
                self->tail = head;
                self->length = 1;
            }
        } else {
            s3_linked_node next = new_linked_node();

            if (next != NULL) {
                next->value = value;
                next->next = NULL;

                if (self->head->next == NULL) {
                    self->head->next = next;
                    next->prev = self->head;
                    self->tail = next;
                } else {
                    next->prev = self->tail;
                    self->tail->next = next;
                    self->tail = next;
                }

                self->length += 1;
            }
        }
    }
}


/* Used to add a new value to the front of the linked list. */
static void append_to_the_front_of_the_list(s3_list_t* self, s3_value_t value)
{
    if (self != NULL) {
        if (self->head == NULL) {
            s3_linked_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                self->head = head;
                self->tail = head;
                self->length = 1;
            }
        } else {
            s3_linked_node prev = new_linked_node();

            if (prev != NULL) {
                prev->value = value;

                if (self->tail->prev == NULL) {
                    self->tail->prev = prev;
                    prev->next = self->tail;
                    self->head = prev;
                } else {
                    prev->next = self->head;
                    self->head->prev = prev;
                    self->head = prev;
                }

                self->length += 1;
            }
        }
    }
}


/* Returns the index of a value in the list.
 * If the value was not found the constant `VALUE_NOT_FOUND` is
 * returned instead.
 * */
static int get_index_of_value(s3_list_t* self, s3_value_t value)
{
    s3_linked_node node = NULL;
    unsigned idx = 0;

    for (node = self->head, idx = 0 ; node != NULL ; node = node->next, ++idx)
        if (node->value == value)
            return idx;

    return VALUE_NOT_FOUND;
}


/* Returns a node at the given index. */
static s3_linked_node get_node_at_index(s3_list_t* list, unsigned index)
{
#ifdef _MAKE_ROBUST_CHECK
    assert(index >= 0);
#endif

    if (list != NULL && index < list->length) {
        s3_linked_node node = NULL;
        unsigned int i = 0;
        float mid_index = (float) list->length / 2;

        if (index < mid_index) {
            /* Forward search */
            i = 0;
            node = list->head;
            while (i < index && node != NULL) {
                node = node->next;
                i += 1;
            }
        } else {
            /* Backward search */
            i = list->length - 1;
            node = list->tail;
            while (i > index && node != NULL) {
                node = node->prev;
                i -= 1;
            }
        }

#ifdef _MAKE_ROBUST_CHECK
        assert(i == index);
        assert(node != NULL);
#endif

        return node;
    }

    return NULL;
}


/* Returns the value at the given index. NULL will be returned
 * by default for out of bound indexes.
 * */
static s3_value_t get_value_at_index(s3_list_t* self, unsigned idx)
{
#ifdef _MAKE_ROBUST_CHECK
    assert(idx >= 0);
#endif

#define DEFAULT_RETURN_TYPE NULL

    if (self != NULL && idx < self->length) {
        s3_linked_node node = get_node_at_index(self, idx);

        if (node != NULL)
            return node->value;
    }

    return DEFAULT_RETURN_TYPE;
}


/* Removes the value at the given index. */
static void remove_at_index(s3_list_t* self, unsigned index)
{
#ifdef _MAKE_ROBUST_CHECK
    assert(index >= 0);
    assert(self->length >= 0); // invariant
#endif

    if (self != NULL && index < self->length) {
        s3_linked_node node = get_node_at_index(self, index);

        if (node != NULL) {
            if (node->prev != NULL)
                node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;

            if (node == self->head)
                self->head = node->next;
            if (node == self->tail)
                self->tail = node->prev;

            node->next = NULL;
            node->prev = NULL;

            free(node);

            node = NULL;
            self->length -= 1;
        }

#ifdef _MAKE_ROBUST_CHECK
        assert(self->length >= 0); // invariant
        assert(node == NULL);
#endif
    }
}


/* Completely removes the value from the list. */
static void remove_all(s3_list_t* self, s3_value_t value)
{
    int index = VALUE_NOT_FOUND;
    while ((index = get_index_of_value(self, value)) != VALUE_NOT_FOUND) {
        remove_at_index(self, (unsigned) index);
    }
#ifdef _MAKE_ROBUST_CHECK
    assert(get_index_of_value(self, value) == VALUE_NOT_FOUND);
#endif
}

/* Returns the string representation of a list. */
char* list_repr(s3_list_t* self)
__LIST_REPR_ALGORITHM(self, "[", "]", ", ", FORWARD)


/* Prints a linked list. */
void display_list(s3_list_t* self)
{
    char* repr = list_repr(self);
    printf("%s", repr);
    free(repr);
}


/* Allocates and returns a new linked list, if possible. */
extern s3_list_t* s3_new_list(void)
{
    s3_list_t* list = (s3_list_t*) malloc(sizeof(s3_list_t));

    if (list != NULL) {
        /* The allocation was made gracefully. */
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;

        list->append_back = &append_to_the_back_of_the_list;
        list->append_front = &append_to_the_front_of_the_list;
        list->index = &get_index_of_value;
        list->get = &get_value_at_index;
        list->remove_at_index = &remove_at_index;
        list->remove_all = &remove_all;
        list->display = &display_list;
        list->repr = &list_repr;

        return list;
    } else /* The allocation could not be made. */
        return NULL;
}


/* Used to free the nodes of a linked list recursivelly. */
static void free_node(s3_linked_node* node)
{
    if (*node != NULL) {
        if ((*node)->next != NULL)
            free_node(&(*node)->next);

        if ((*node)->value != NULL)
            free((*node)->value);

        free(*node);
        *node = NULL;
    }
#ifdef _MAKE_ROBUST_CHECK
    assert(*node == NULL);
#endif
}


/* Used to free the linked list and its nodes. */
extern void s3_list_free(s3_list_t** list)
{
    if (*list != NULL) {
        free_node(&(*list)->head);
        free(*list);
        *list = NULL;
    }
#ifdef _MAKE_ROBUST_CHECK
    assert(*list == NULL);
#endif
}
