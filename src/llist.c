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
extern void s3_list_append_back(s3_list_t* list, s3_value_t value)
{
    if (list != NULL) {
        if (list->head == NULL) {
            s3_linked_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                list->head = head;
                list->tail = head;
                list->length = 1;
            }
        } else {
            s3_linked_node next = new_linked_node();

            if (next != NULL) {
                next->value = value;
                next->next = NULL;

                if (list->head->next == NULL) {
                    list->head->next = next;
                    next->prev = list->head;
                    list->tail = next;
                } else {
                    next->prev = list->tail;
                    list->tail->next = next;
                    list->tail = next;
                }

                list->length += 1;
            }
        }
    }
}


/* Used to add a new value to the front of the linked list. */
extern void s3_list_append_front(s3_list_t* list, s3_value_t value)
{
    if (list != NULL) {
        if (list->head == NULL) {
            s3_linked_node head = new_linked_node();

            if (head != NULL) {
                head->value = value;
                list->head = head;
                list->tail = head;
                list->length = 1;
            }
        } else {
            s3_linked_node prev = new_linked_node();

            if (prev != NULL) {
                prev->value = value;

                if (list->tail->prev == NULL) {
                    list->tail->prev = prev;
                    prev->next = list->tail;
                    list->head = prev;
                } else {
                    prev->next = list->head;
                    list->head->prev = prev;
                    list->head = prev;
                }

                list->length += 1;
            }
        }
    }
}


/* Returns the index of a value in the list.
 * If the value was not found the constant `S3_VALUE_NOT_FOUND` is
 * returned instead.
 * */
extern int s3_list_get_first_index(s3_list_t* list, s3_value_t value)
{
    s3_linked_node node = NULL;
    unsigned idx = 0;

    for (node = list->head, idx = 0 ; node != NULL ; node = node->next, ++idx)
        if (s3_value_compare(node->value, value) == S3_VALUE_EQUAL)
            return idx;

    return S3_VALUE_NOT_FOUND;
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
extern s3_value_t s3_list_get_value(s3_list_t* list, unsigned idx)
{
#ifdef _MAKE_ROBUST_CHECK
    assert(idx >= 0);
#endif

#define DEFAULT_RETURN_TYPE NULL

    if (list != NULL && idx < list->length) {
        s3_linked_node node = get_node_at_index(list, idx);

        if (node != NULL)
            return node->value;
    }

    return DEFAULT_RETURN_TYPE;
}


/* Removes the value at the given index. */
extern void s3_list_remove_at_index(s3_list_t* list, unsigned index)
{
#ifdef _MAKE_ROBUST_CHECK
    assert(index >= 0);
    assert(list->length >= 0); // invariant
#endif

    if (list != NULL && index < list->length) {
        s3_linked_node node = get_node_at_index(list, index);

        if (node != NULL) {
            if (node->prev != NULL)
                node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;

            if (node == list->head)
                list->head = node->next;
            if (node == list->tail)
                list->tail = node->prev;

            node->next = NULL;
            node->prev = NULL;

            free(node->value);
            free(node);

            node = NULL;
            list->length -= 1;
        }

#ifdef _MAKE_ROBUST_CHECK
        assert(list->length >= 0); // invariant
        assert(node == NULL);
#endif
    }
}


/* Completely removes the value from the list. */
extern void s3_list_remove_value(s3_list_t* list, s3_value_t value)
{
    int index = S3_VALUE_NOT_FOUND;
    while ((index = s3_list_get_first_index(list, value)) != S3_VALUE_NOT_FOUND) {
        s3_list_remove_at_index(list, (unsigned) index);
    }
#ifdef _MAKE_ROBUST_CHECK
    assert(s3_list_get_first_index(list, value) == S3_VALUE_NOT_FOUND);
#endif
}

/* Returns the string representation of a list. */
extern char* s3_list_repr(s3_list_t* list)
__LIST_REPR_ALGORITHM(list, "[", "]", ", ", FORWARD)


/* Prints a linked list. */
extern void s3_list_display(s3_list_t* list)
{
    char* repr = s3_list_repr(list);
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

        list->append_back = &s3_list_append_back;
        list->append_front = &s3_list_append_front;
        list->index = &s3_list_get_first_index;
        list->get = &s3_list_get_value;
        list->remove_at_index = &s3_list_remove_at_index;
        list->remove_all = &s3_list_remove_value;
        list->display = &s3_list_display;
        list->repr = &s3_list_repr;

        return list;
    } else /* The allocation could not be made. */
        return NULL;
}


/* Used to free the nodes of a linked list recursivelly. */
static void list_node_free(s3_linked_node* node)
{
    if (*node != NULL) {
        if ((*node)->next != NULL)
            list_node_free(&(*node)->next);

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
        list_node_free(&(*list)->head);
        free(*list);
        *list = NULL;
    }
#ifdef _MAKE_ROBUST_CHECK
    assert(*list == NULL);
#endif
}
