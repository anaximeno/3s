#include "../include/core.h"
#include "../include/llist.h"

#include <stdlib.h>
#include <stdio.h>


typedef struct _linked_node* _l_node;


/* Creates a new linked node. */
static _l_node new_linked_node(void)
{
    _l_node node = (_l_node) malloc(sizeof(struct _linked_node));

    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->value = 0;
    }

    return node;
}


/* Used to add a new value to the linked list. */
static void add_to_linked_list(l_list* self, value_t value)
{
    if (self != NULL) {
        if (self->head == NULL) {
            _l_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                self->head = head;
                self->tail = head;
                self->length = 1;
            }
        } else {
            _l_node next = new_linked_node();

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
                    self->tail = self->tail->next;
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
static int get_index_of_value(l_list* self, value_t value)
{
    _l_node node = NULL;
    unsigned idx = 0;

    for (node = self->head, idx = 0 ; node != NULL ; node = node->next, ++idx)
        if (node->value == value)
            return idx;

    return VALUE_NOT_FOUND;
}


/* Returns a node at the given index. */
static _l_node get_node_at_index(l_list* list, unsigned index)
{
    if (list != NULL && index < list->length) {
        _l_node node = NULL;
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

        return node;
    }

    return NULL;
}


/* Returns the value at the given index. Zero will be returned
 * by default for out of bound indexes.
 * */
static value_t get_value_at_index(l_list* self, unsigned idx)
{
#define DEFAULT_RETURN_TYPE 0

    if (self != NULL && idx < self->length) {
        _l_node node = get_node_at_index(self, idx);

        if (node != NULL)
            return node->value;
    }

    return DEFAULT_RETURN_TYPE;
}


/* Removes the value at the given index. */
static void remove_at_index(l_list* self, unsigned index)
{
    if (self != NULL && index < self->length) {
        _l_node node = get_node_at_index(self, index);

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
    }
}


/* Completely removes the value from the list. */
static void remove_all(l_list* self, value_t value)
{
    int index = VALUE_NOT_FOUND;
    while ((index = get_index_of_value(self, value)) != VALUE_NOT_FOUND) {
        remove_at_index(self, (unsigned) index);
    }
}


/* Prints a linked list. Currently it only works for int types. */
void print_list(l_list* self)
{
    putchar('[');
    for (unsigned i = 0 ; i < self->length ; ++i) {
        printf("%d", self->get(self, i));
        if (i != self->length - 1)
            printf(", ");
    }
    putchar(']');
}


/* Allocates and returns a new linked list, if possible. */
extern l_list* new_list(void)
{
    l_list* list = (l_list*) malloc(sizeof(l_list));

    if (list != NULL) {
        /* The allocation was made gracefully. */
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;

        list->add = &add_to_linked_list;
        list->index = &get_index_of_value;
        list->get = &get_value_at_index;
        list->remove_at_index = &remove_at_index;
        list->remove_all = &remove_all;
        list->print = &print_list;

        return list;
    } else /* The allocation could not be made. */
        return NULL;
}


/* Used to free the nodes of a linked list recursivelly. */
static void free_node(_l_node* node)
{
    if (*node != NULL) {
        if ((*node)->next != NULL)
            free_node(&(*node)->next);

        free(*node);
        *node = NULL;
    }
}


/* Used to free the linked list and its nodes. */
extern void free_list(l_list** list)
{
    if (*list != NULL) {
        free_node(&(*list)->head);
        free(*list);
        *list = NULL;
    }
}
