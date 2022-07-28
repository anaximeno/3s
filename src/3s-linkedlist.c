#include "../include/3s-structs.h"

#include <stdlib.h>

typedef struct _linked_node* _l_node;


/* Creates a new linked node. */
static _l_node new_linked_node(void)
{
    _l_node node = (_l_node) malloc(sizeof(struct _linked_node));

    if (node != NULL) {
        node->next = NULL;
        node->value = 0;
    }

    return node;
}


/* Used to add a new value to the linked list. */
static void add_to_linked_list(l_list* this, value_t value)
{
    if (this != NULL) {
        if (this->head == NULL) {
            this->head = new_linked_node();

            if (this->head != NULL) {
                this->head->value = value;
                this->tail = this->head;
                this->length = 1;
            }
        } else {
            _l_node next = new_linked_node();

            if (next != NULL) {
                next->value = value;
                next->next = NULL;
                this->tail->next = next;
                this->tail = next;
                this->length += 1;
            }
        }
    }
}


static int get_index_of_value(l_list* this, value_t value) {
    _l_node node = NULL;
    unsigned idx = 0;

    for (node = this->head ; node != NULL ; node = node->next, ++idx) {
        if (node->value == value) {
            return idx;
        }
    }

    return VALUE_NOT_FOUND;
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

        return list;
    } else {
        /* The allocation could not be made. */
        return NULL;
    }
}