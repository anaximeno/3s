#include "../include/3s-structs.h"

#include <stdlib.h>

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
static void add_to_linked_list(l_list* this, value_t value)
{
    if (this != NULL) {
        if (this->head == NULL) {
            _l_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                this->head = head;
                this->tail = head;
                this->length = 1;
            }
        } else {
            _l_node next = new_linked_node();

            if (next != NULL) {
                next->value = value;
                next->next = NULL;
                next->prev = this->tail;
                this->tail->next = next;
                this->tail = this->tail->next;
                this->length += 1;
            }
        }
    }
}


/* Returns the index of a value in the list.
 * If the value was not found the constant `VALUE_NOT_FOUND` is
 * returned instead.
 * */
static int get_index_of_value(l_list* this, value_t value)
{
    _l_node node = NULL;
    unsigned idx = 0;

    for (node = this->head ; node != NULL ; node = node->next, ++idx)
        if (node->value == value)
            return idx;

    return VALUE_NOT_FOUND;
}


/* Returns the value at the given index. Zero will be returned
 * by default for out of bound indexes.
 * */
static value_t get_value_at_index(l_list* this, unsigned idx)
{
#define DEFAULT_RETURN_TYPE 0

    if (this != NULL && idx < this->length) {
        _l_node node = NULL;
        unsigned int i = 0;
        float mid_idx = (float) this->length / 2;

        if (idx < mid_idx) {
            /* Forward search */
            i = 0;
            node = this->head;
            while (i < idx && node != NULL) {
                node = node->next;
                i += 1;
            }
        } else {
            /* Backward search */
            i = this->length - 1;
            node = this->tail;
            while (i > idx && node != NULL) {
                node = node->prev;
                i -= 1;
            }
        }

        return node != NULL ? node->value : DEFAULT_RETURN_TYPE;
    }

    return DEFAULT_RETURN_TYPE;
}


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

        return list;
    } else /* The allocation could not be made. */
        return NULL;
}

static void free_node(_l_node* node) {
    if ((*node)->next != NULL)
        free_node(&(*node)->next);

    free(*node);
    *node = NULL;
}

extern void free_list(l_list** list)
{
    free_node(&(*list)->head);
    free(*list);
    *list = NULL;
}