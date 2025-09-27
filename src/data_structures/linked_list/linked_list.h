/**
 * @file linked_list.h
 * @author Zachary Hoagland (zach@zacharyhoagland.com)
 * @brief API for the linked list data structure library.
 * @version 1.0
 * @date 2025-04-03
 *
 * @copyright Copyright Zachary Hoagland (c) 2025
 *
 */
#ifndef _DSA_LINKED_LIST_H_
#define _DSA_LINKED_LIST_H_


#ifdef __cplusplus
    extern "C" {
#endif


/* -------------------- Public Includes --------------------------------- */
#include "macros.h"
#include <stdint.h>
#include <stdbool.h>

/* -------------------- Public Macros/Defines --------------------------- */
typedef struct LinkedListHandle__* LinkedListHandle;

    /* -------------------- Public Enums ------------------------------------ */
typedef enum dsa_list_type {
    SINGLY_LINKED_LIST,
    DOUBLY_LINKED_LIST,
    CIRCULARLY_LINKED_LIST,
} dsa_list_type_t;

/* -------------------- Public Structs ---------------------------------- */


/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */

/* Init / Destroy Functions */
LinkedListHandle linked_list_initialize(dsa_list_type_t list_type, void *data);
int linked_list_delete(LinkedListHandle *handle);
int linked_list_mapped_action_on_delete(LinkedListHandle *handle, void(*mapping_fnc)(void *data));

/* Insert Functions */
int linked_list_insert_front(LinkedListHandle handle, void *data);
int linked_list_insert_back(LinkedListHandle handle, void *data);
int linked_list_insert_at(LinkedListHandle handle, uint32_t location, void *data);
int linked_list_insert_sorted(LinkedListHandle handle, void *data, int(*cmpfunc)(void* a,void* b));

/* Remove Functions */
int linked_list_remove_front(LinkedListHandle handle, void (*fnc_on_removal)(void *data));
int linked_list_remove_back(LinkedListHandle handle, void (*fnc_on_removal)(void *data));
int linked_list_remove_node(LinkedListHandle handle, void *data, void (*fnc_on_removal)(void *data));
int linked_list_remove_at(LinkedListHandle handle, uint32_t location, void(*fnc_on_removal)(void *data));

/* Retrieval Functions*/
void *linked_list_get_back(LinkedListHandle handle);
void *linked_list_get_at(LinkedListHandle handle, uint32_t location);
void *get_front(LinkedListHandle handle);
int32_t linked_list_search(LinkedListHandle handle, void *data);
bool linked_list_is_empty(LinkedListHandle handle);
int linked_list_get_list_size(LinkedListHandle handle);

/* Iterators */
void *linked_list_iter_previous(LinkedListHandle handle, void *last_data_ptr);
void *linked_list_iter_next(LinkedListHandle handle, void *last_data_ptr);

/* Utility Functions */
int linked_list_map_data(LinkedListHandle handle, void(*mapping_fnc)(void* data));
void linked_list_print(LinkedListHandle handle, void(*data_printer)(void *));

/* Error Functions */
#ifdef _DSA_ERROR_H_
int linked_list_get_error_code(LinkedListHandle handle);
char *linked_list_get_error_message(LinkedListHandle handle);
#endif /* _DSA_ERROR_H_ */

#ifdef __cplusplus
    }
#endif


#endif /* _DSA_LINKED_LIST_H_ */