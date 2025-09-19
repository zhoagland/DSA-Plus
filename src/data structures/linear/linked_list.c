/**
* @file linked_list.c
* @author Zachary Hoagland (you@domain.com)
* @brief
* @version 0.1
* @date 2025-04-03
*
* @copyright Copyright (c) 2025
*
*/
/* -------------------- Private Includes ------------------------------------------- */
#include "../../include/linked_list.h"
#include <stdint.h>
#include <stdlib.h>
#include <vcruntime.h>

/* -------------------- Private Macros/Defines ------------------------------------- */
typedef uint32_t dsa_linked_list_h;

/* -------------------- Private Enums ---------------------------------------------- */


/* -------------------- Private Structs -------------------------------------------- */
typedef struct _dsa_node {
    struct _dsa_node *next_node;
    struct _dsa_node *previous_node;
    void *data;
} dsa_node_t;

typedef struct _dsa_linked_list_internal {
    struct LinkedListHandle__ handle;
    dsa_node_t *head;
    dsa_node_t *tail;
    dsa_list_type_t list_type;
    uint32_t list_length;
} dsa_linked_list_internal_t;

/* -------------------- Private (static) Vars -------------------------------------- */

/* -------------------- Private (static) Function Declarations --------------------- */

/* -------------------- Public (global) Vars --------------------------------------- */


/* -------------------- Private and Public Function Definitions -------------------- */
LinkedListHandle initialize_linked_list(dsa_list_type_t list_type, void *data) {

    dsa_linked_list_internal_t *list = calloc(1, sizeof(dsa_linked_list_internal_t));

    list->list_type = list_type;
    list->list_length = 0;
    list->head = NULL;
    list->tail = NULL;

    return (LinkedListHandle)list;
}


int linked_list_insert_front(LinkedListHandle handle, void *data) {

    dsa_linked_list_internal_t *list = (dsa_linked_list_internal_t*)handle;

    dsa_node_t *previous_head = list->head;
    list->head = (dsa_node_t*)calloc(1, sizeof(dsa_node_t));
    list->head->data = data;

    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            list->head->next_node = previous_head;
            previous_head->previous_node = NULL;
            list->head->previous_node = NULL;
            break;
        case DOUBLY_LINKED_LIST:
            list->head->previous_node = NULL;
            list->head->next_node = previous_head;
            previous_head->previous_node = list->head;
            break;
        case CIRCULARLY_LINKED_LIST:
            list->head->next_node = previous_head;
            previous_head->previous_node = list->head;
            list->head->previous_node = list->tail;
            break;
    }

    list->list_length++;

    return  0;
}

int linked_list_insert_back(LinkedListHandle handle, void *data) {
    dsa_linked_list_internal_t *list = (dsa_linked_list_internal_t*)handle;

    dsa_node_t *previous_tail = list->tail;
    list->tail = (dsa_node_t*)calloc(1, sizeof(dsa_node_t));
    list->tail->data = data;

    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            previous_tail->next_node = list->tail;
            list->tail->next_node = NULL;
            list->tail->previous_node = NULL;
            break;
        case DOUBLY_LINKED_LIST:
            previous_tail->next_node = list->tail;
            list->tail->next_node = NULL;
            list->tail->previous_node = previous_tail;
            break;
        case CIRCULARLY_LINKED_LIST:
            previous_tail->next_node = list->tail;
            list->tail->next_node = list->head;
            list->tail->previous_node = previous_tail;
            break;
    }

    list->list_length++;

    return 0;
}

int linked_list_insert_at(LinkedListHandle handle, uint32_t location, void *data) {

    dsa_linked_list_internal_t *list = (dsa_linked_list_internal_t*)handle;

    if(location >= list->list_length) {
        return linked_list_insert_back(handle, data);
    }
    if(location == 0) {
        return  linked_list_insert_front(handle, data);
    }

    dsa_node_t *current_node = list->head;
    dsa_node_t *next_node = list->head->next_node;

    for(size_t loc = 0; loc < location; loc++) {
        current_node = current_node->next_node;
        next_node = current_node->next_node;
    }

    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            current_node->next_node = (dsa_node_t*)calloc(1, sizeof(dsa_node_t));
            current_node->next_node->data = data;
            current_node->next_node->next_node=next_node;
            break;

        case CIRCULARLY_LINKED_LIST:
        case DOUBLY_LINKED_LIST:
            current_node->next_node = (dsa_node_t*)calloc(1, sizeof(dsa_node_t));
            current_node->next_node->data = data;
            current_node->next_node->next_node=next_node;
            current_node->next_node->previous_node=current_node;
            next_node->previous_node=current_node->next_node;
            break;
    }

    list->list_length++;

    return 0;
}

int linked_list_insert_sorted(LinkedListHandle handle, void(*sorter(void*,void*))) {
    return 0;
}

int linked_list_remove_front(LinkedListHandle handle) {
    return 0;
}

int linked_list_remove_back(LinkedListHandle handle) {
    return 0;
}

int linked_list_remove_node(LinkedListHandle handle) {
    return 0;
}

int linked_list_remove_at(LinkedListHandle handle) {
    return 0;
}

int linked_list_get_back(LinkedListHandle handle) {
    return 0;
}

int linked_list_get_at(LinkedListHandle handle) {
    return 0;
}

void *linked_list_search(LinkedListHandle handle, void *data) {

    return NULL;
}

bool linked_list_is_empty(LinkedListHandle handle) {
    return ((((dsa_linked_list_internal_t*)handle)->list_length == 0) ? true : false);
}

int linked_list_get_list_size(LinkedListHandle handle) {
    return ((dsa_linked_list_internal_t*)handle)->list_length;
}

inline void *get_front(LinkedListHandle handle) {
    return ((dsa_linked_list_internal_t*)handle)->head->data;
}

void linked_list_print(LinkedListHandle handle, void(*data_printer(void))) {

}