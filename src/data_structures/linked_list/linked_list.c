/**
 * @file linked_list.c
 * @author Zachary Hoagland (zach@zacharyhoagland.com)
 * @brief
 * @version 0.1
 * @date 2025-04-03
 *
 * @copyright Copyright (c) 2025
 *
 */
/* -------------------- Private Includes ------------------------------------------- */
#include "linked_list.h"
#include "linked_list_internal.h"


#ifndef _CVI_LIB_
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
#else
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdio.h"
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdint.h"
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdlib.h"
#endif  // !_CVI_LIB_

/* -------------------- Private Macros/Defines ------------------------------------- */
DECLARE_HANDLE(LinkedListHandle);

/* -------------------- Private Macros/Defines ------------------------------------- */
/* -------------------- Private Enums ---------------------------------------------- */


/* -------------------- Private Structs -------------------------------------------- */


/* -------------------- Private (static) Vars -------------------------------------- */

#ifdef __DSA_ERROR_HANDLING
const char *ll_error_messages[] = {
    "Success",
};
#endif /* __DSA_ERROR_HANDLING */

/* -------------------- Private (static) Function Declarations --------------------- */

#ifdef __DSA_ERROR_HANDLING
static dsa_ll_error_codes_t get_error_code_override_(void *p_error);
static char                *get_error_message_override_(void *p_error);
static void                 ll_error_ctor(dsa_ll_error_t *const self);
#endif /* __DSA_ERROR_HANDLING */
/* -------------------- Public (global) Vars --------------------------------------- */


/* -------------------- Private and Public Function Definitions -------------------- */

/* Error Handling Class Methods */
#ifdef __DSA_ERROR_HANDLING
char *get_error_message_override_(void *p_error) {
    dsa_ll_error_t *local_error = ((dsa_error_t *)p_error);

    return ll_error_messages[local_error->error_code];
}

static dsa_ll_error_codes_t get_error_code_override_(void *p_error) {
    dsa_ll_error_t *local_error = ((dsa_error_t *)p_error);

    return (local_error->error_code) * -1;
}

static void ll_error_ctor(dsa_ll_error_t *const self) {
    static const dsa_error_vtbl_t glob_error_vtbl = {.get_error_code = &get_error_code_override_,
                                                     .get_error_message =
                                                         &get_error_message_override_};

    error_ctor(&self->glob_error);

    self->glob_error.p_vtbl = &glob_error_vtbl;
}

int linked_list_get_error_code(LinkedListHandle handle) {
    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    return (int)get_error_code(&list->error);
}

char *linked_list_get_error_message(LinkedListHandle handle) {
    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    return get_error_message(&list->error);
}

#endif /* __DSA_ERROR_HANDLING */

/* Module Methods */

LinkedListHandle __cdecl linked_list_initialize(dsa_list_type_t list_type, void *data) {
    dsa_linked_list_control_block_t *list =
        (dsa_linked_list_control_block_t *)calloc(1, sizeof(dsa_linked_list_control_block_t));

    if (!list) {
        return NULL;
    }

    list->list_type   = list_type;
    list->list_length = 0;
    list->head        = NULL;
    list->tail        = NULL;

    if (data) {
        linked_list_insert_front((LinkedListHandle)list, data);
    }

    return (LinkedListHandle)list;
}

int __cdecl linked_list_delete(LinkedListHandle *handle) {
    VALIDATE_HANDLE(*handle, -1);

    dsa_node_t *next_node = NULL;

    // Loop through all the nodes in the list.
    for (dsa_node_t *current_node = (*((dsa_linked_list_control_block_t **)handle))->head;
         current_node != NULL;) {
        // Store the next node into memory;
        next_node = current_node->next_node;

        // Check to see if node points to itself
        if (next_node == current_node) {
            next_node = NULL;
        }

        // Free the current node.
        free(current_node);
        // Set the next node as the current node
        current_node = next_node;
    }

    // Free the control block
    free(*(dsa_linked_list_control_block_t **)handle);
    *handle = NULL;

    return 0;
}

int __cdecl linked_list_mapped_action_on_delete(LinkedListHandle *handle,
                                                void(__cdecl *mapping_fnc)(void *data)) {
    VALIDATE_HANDLE(*handle, -1);

    linked_list_map_data(*handle, mapping_fnc);
    linked_list_delete(handle);
    return 0;
}

int __cdecl linked_list_insert_front(LinkedListHandle handle, void *data) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    dsa_node_t *previous_head = list->head;
    list->head                = (dsa_node_t *)calloc(1, sizeof(dsa_node_t));

    if (!list->head) {
        return -1;
    }

    list->head->data = data;

    if (list->list_length == 0) {
        list->tail = list->head;
    }

    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            list->head->next_node     = previous_head;
            list->head->previous_node = NULL;

            if (previous_head) {
                previous_head->previous_node = NULL;
            }

            break;

        case DOUBLY_LINKED_LIST:
            list->head->previous_node = NULL;

            if (previous_head) {
                previous_head->previous_node = list->head;
            }

            list->head->next_node = previous_head;

            break;

        case CIRCULAR_SINGLY_LINKED_LIST:
            if (previous_head) {
                list->head->next_node        = previous_head;
                previous_head->previous_node = list->head;
            } else if (list->list_length == 0) {
                list->head->next_node = list->head;
            } else {
                list->head->next_node = NULL;
            }

            list->head->previous_node = list->tail;

            break;

        case CIRCULAR_DOUBLY_LINKED_LIST:
            // TODO
           break;
    }

    list->list_length++;

    return 0;
}

int __cdecl linked_list_insert_back(LinkedListHandle handle, void *data) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list          = (dsa_linked_list_control_block_t *)handle;
    dsa_node_t                      *previous_tail = list->tail;

    if (list->list_length == 0) {
        return linked_list_insert_front(handle, data);
    }

    list->tail = (dsa_node_t *)calloc(1, sizeof(dsa_node_t));

    if (!list->tail) {
        return -1;
    }

    list->tail->data = data;

    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            previous_tail->next_node  = list->tail;
            list->tail->next_node     = NULL;
            list->tail->previous_node = NULL;
            break;
        case DOUBLY_LINKED_LIST:
            previous_tail->next_node  = list->tail;
            list->tail->next_node     = NULL;
            list->tail->previous_node = previous_tail;
            break;
        case CIRCULAR_SINGLY_LINKED_LIST:
            previous_tail->next_node  = list->tail;
            list->tail->next_node     = list->head;
            list->tail->previous_node = previous_tail;
            break;
        case CIRCULAR_DOUBLY_LINKED_LIST:
            // TODO 
            break;
    }

    list->list_length++;

    return 0;
}

int __cdecl linked_list_insert_at(LinkedListHandle handle, uint32_t location, void *data) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    if (location >= list->list_length) {
        return linked_list_insert_back(handle, data);
    }
    if (location == 0) {
        return linked_list_insert_front(handle, data);
    }

    dsa_node_t *current_node = list->head;
    dsa_node_t *next_node    = list->head->next_node;

    for (size_t loc = 0; loc < location - 1; loc++) {
        current_node = current_node->next_node;
        next_node    = current_node->next_node;
    }

    current_node->next_node = (dsa_node_t *)calloc(1, sizeof(dsa_node_t));

    if (!current_node->next_node) {
        return -1;
    }

    switch (list->list_type) {
       case CIRCULAR_SINGLY_LINKED_LIST: 
       case SINGLY_LINKED_LIST:
            current_node->next_node->data      = data;
            current_node->next_node->next_node = next_node;
            break;

        
        case CIRCULAR_DOUBLY_LINKED_LIST:
        case DOUBLY_LINKED_LIST:
            current_node->next_node->data          = data;
            current_node->next_node->next_node     = next_node;
            current_node->next_node->previous_node = current_node;
            next_node->previous_node               = current_node->next_node;
            break;
    }

    list->list_length++;

    return 0;
}

int __cdecl linked_list_insert_sorted(LinkedListHandle handle, void *data,
                                      int(__cdecl *cmpfunc)(void *a, void *b)) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list      = (dsa_linked_list_control_block_t *)handle;
    uint32_t                         loop_iter = 0;
    dsa_node_t                      *node      = NULL;
    node                                       = list->head;

    do {
        // 	  Cmp func logic
        //    a negative result if a < b
        //    0 if a == b
        //    a positive result if a > b

        // Check to see if current node is the tail. If so just insert at end.
        if ((node) == ((dsa_linked_list_control_block_t *)handle)->tail) {
            return linked_list_insert_back(handle, data);
        }

        //
        int cmp_result = (*cmpfunc)(data, node->data);
        if (cmp_result <= 0) {
            return linked_list_insert_at(handle, loop_iter, data);
        }
        // new data is greater than old data
        else {
            // Continue looping
        }
        node = node->next_node;
        loop_iter++;
    } while (node);

    list->list_length++;
    return 0;
}

int __cdecl linked_list_remove_front(LinkedListHandle handle,
                                     void(__cdecl *fnc_on_removal)(void *data)) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list     = (dsa_linked_list_control_block_t *)handle;
    dsa_node_t                      *old_head = list->head;

    // Check to see if there are nodes to remove
    if (list->list_length == 0) {
        return -1;
    }

    // Update the head to be the next node in the list
    list->head = old_head->next_node;

    // If not singly linked the head needs to point to the previous of the old head.
    if (list->list_type != SINGLY_LINKED_LIST) {
        list->head->previous_node = old_head->previous_node;
    } else {
        list->head->previous_node = NULL;
    }

    if (fnc_on_removal) {
        (*fnc_on_removal)(old_head->data);
    }

    free(old_head);
    old_head = NULL;

    // Decrement the node length counter
    list->list_length--;
    return 0;
}

int __cdecl linked_list_remove_back(LinkedListHandle handle,
                                    void(__cdecl *fnc_on_removal)(void *data)) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list     = (dsa_linked_list_control_block_t *)handle;
    dsa_node_t                      *old_tail = list->tail;

    // Check to see if there are nodes to remove
    if (list->list_length == 0) {
        return -1;
    }

    // If not singly linked the head needs to point to the previous of the old head.
    if (list->list_type != SINGLY_LINKED_LIST) {
        // Update the head to be the next node in the list
        list->tail            = old_tail->previous_node;
        list->tail->next_node = old_tail->next_node;
    } else {
        for (dsa_node_t *current_node = list->head; current_node;
             current_node             = current_node->next_node) {
            // If not tail
            if (current_node->next_node) {
                // If the nodes next node is the tail
                if (current_node->next_node->next_node == NULL) {
                    // The current node becomes new tail because old tail is being removed.
                    list->tail = current_node;
                    // Singly linked list so it points to NULL.
                    list->tail->next_node = NULL;
                }
            }
        }
    }

    if (fnc_on_removal) {
        (*fnc_on_removal)(old_tail->data);
    }

    free(old_tail);
    old_tail = NULL;

    // Decrement the node length counter
    list->list_length--;
    return 0;
}

int __cdecl linked_list_remove_node(LinkedListHandle handle, void *data,
                                    void(__cdecl *fnc_on_removal)(void *data)) {
    return linked_list_remove_at(handle, linked_list_search(handle, data), fnc_on_removal);
}

int __cdecl linked_list_remove_at(LinkedListHandle handle, uint32_t location,
                                  void(__cdecl *fnc_on_removal)(void *data)) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list          = (dsa_linked_list_control_block_t *)handle;
    dsa_node_t                      *previous_node = NULL;
    dsa_node_t                      *current_node  = list->head;
    dsa_node_t                      *next_node     = NULL;

    // If node is loc 0 remove front
    if (location == 0) {
        return linked_list_remove_front(handle, fnc_on_removal);
    }

    // If node is end remove back
    if (location == (list->list_length - 1)) {
        return linked_list_remove_back(handle, fnc_on_removal);
    }

    // Check to verify location is valid.
    if (location < 0 || location > list->list_length) {
        return -1;
    }

    // Check to see if there are nodes to remove
    if (list->list_length == 0) {
        return -1;
    }

    for (size_t loc = 0; loc < location; loc++) {
        previous_node = current_node;
        current_node  = previous_node->next_node;
        next_node     = current_node->next_node;
    }

    previous_node->next_node = next_node;

    if (list->list_type != SINGLY_LINKED_LIST) {
        next_node->previous_node = previous_node;
    }

    if (fnc_on_removal) {
        (*fnc_on_removal)(current_node->data);
    }

    free(current_node);
    current_node = NULL;

    // Decrement the node length counter
    list->list_length--;
    return 0;
}

void *__cdecl linked_list_get_back(LinkedListHandle handle) {
    VALIDATE_HANDLE(handle, NULL);

    return ((dsa_linked_list_control_block_t *)handle)->tail->data;
}

void *__cdecl linked_list_get_at(LinkedListHandle handle, uint32_t location) {
    VALIDATE_HANDLE(handle, NULL);

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;
    dsa_node_t                      *node = list->head;

    if (!node) {
        return node;
    }

    // If not singly linked list we can find which way is faster to traverse forward of backwards
    if (list->list_type != SINGLY_LINKED_LIST) {
        // Location is bigger than half go from back of the list.
        if (location > (list->list_length) / 2) {
            node = list->tail;

            for (uint32_t node_number = list->list_length; node_number == location; node_number--) {
                node = node->previous_node;
            }

            return node->data;
        }
    }

    // If singly linked or from the front of the list is faster
    for (uint32_t node_number = 0; node_number != location && node; node_number++) {
        node = node->next_node;
    }

    return node ? node->data : NULL;
}

void *__cdecl get_front(LinkedListHandle handle) {
    VALIDATE_HANDLE(handle, NULL);

    return ((dsa_linked_list_control_block_t *)handle)->head->data;
}

int __cdecl linked_list_map_data(LinkedListHandle handle, void(__cdecl *mapping_fnc)(void *data)) {
    VALIDATE_HANDLE(handle, -1);

    dsa_node_t *node = NULL;

    node = ((dsa_linked_list_control_block_t *)handle)->head;

    while (node) {
        (*mapping_fnc)(node->data);
        node = node->next_node;
    };

    return 0;
}

int32_t __cdecl linked_list_search(LinkedListHandle handle, void *data) {
    VALIDATE_HANDLE(handle, -1);

    dsa_linked_list_control_block_t *list          = (dsa_linked_list_control_block_t *)handle;
    size_t                           node_location = 0;

    for (dsa_node_t *current_node = list->head; current_node;
         current_node             = current_node->next_node, node_location++) {
        if (current_node->data == data) {
            return node_location;
        }
    }

    return -1;
}

bool __cdecl linked_list_is_empty(LinkedListHandle handle) {
    VALIDATE_HANDLE(handle, true);

    return ((((dsa_linked_list_control_block_t *)handle)->list_length == 0) ? true : false);
}

int __cdecl linked_list_get_list_size(LinkedListHandle handle) {
    VALIDATE_HANDLE(handle, -1);

    return ((dsa_linked_list_control_block_t *)handle)->list_length;
}

void __cdecl linked_list_print(LinkedListHandle handle,
                               void(__cdecl *data_printer)(FILE *, void *), FILE *output_stream) {
    VALIDATE_HANDLE(handle, );

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    fprintf(output_stream,"List Length: %d\n", list->list_length);

    fprintf(output_stream, "List Type: ");
    switch (list->list_type) {
        case SINGLY_LINKED_LIST:
            fprintf(output_stream, "Singly Linked List\n");
            break;
        case DOUBLY_LINKED_LIST:
            fprintf(output_stream, "Doubly Linked List\n");
            break;
        case CIRCULAR_SINGLY_LINKED_LIST:
            fprintf(output_stream, "Circular Singly Linked List\n");
            break;
        case CIRCULAR_DOUBLY_LINKED_LIST:
            fprintf(output_stream, "Circular Doubly Linked List\n");
            break;
    }

    for (uint32_t node_number = 0; node_number < list->list_length; node_number++) {
        fprintf(output_stream, "Node %d\n Data:\n", node_number);
        (*data_printer)(output_stream, linked_list_get_at(handle, node_number));
        fprintf(output_stream, "\n");
    }

    return;
}

void *__cdecl linked_list_iter_next(LinkedListHandle handle, void *last_data_ptr) {
    VALIDATE_HANDLE(handle, NULL);

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    if (last_data_ptr == NULL) {
        // This is the first call, return the head

        if (list->head) {
            return list->head->data;
        } else {
            return NULL;
        }
    } else {
        // Find the node corresponding to last_data_ptr and return the next one
        dsa_node_t *current = list->head;
        while (current) {
            if (current->data == last_data_ptr) {
                if (current->next_node) {
                    return current->next_node->data;
                } else {
                    return NULL;
                }
            }
            current = current->next_node;
        }
        return NULL;  // Should not happen if last_data_ptr is valid
    }
}

void *__cdecl linked_list_iter_previous(LinkedListHandle handle, void *last_data_ptr) {
    VALIDATE_HANDLE(handle, NULL);

    dsa_linked_list_control_block_t *list = (dsa_linked_list_control_block_t *)handle;

    if (list->list_type == SINGLY_LINKED_LIST) {
        return NULL;
    }

    if (last_data_ptr == NULL) {
        // This is the first call, return the tail
        if (list->tail) {
            return list->tail->data;
        } else {
            return NULL;
        }
    } else {
        // Find the node corresponding to last_data_ptr and return the previous one
        dsa_node_t *current = list->tail;
        while (current) {
            if (current->data == last_data_ptr) {
                if (current->previous_node) {
                    return current->previous_node->data;
                } else {
                    return NULL;
                }
            }
            current = current->previous_node;
        }
        return NULL;  // Should not happen if last_data_ptr is valid
    }
}