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
#include "dsa_macros.h"
#include <stdbool.h>


#ifndef _CVI_LIB_
    #include <stdio.h>
    #include <stdint.h>
#else
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdio.h"
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdint.h"
#endif  // !_CVI_LIB_


/* -------------------- Public Macros/Defines --------------------------- */
typedef struct LinkedListHandle__* LinkedListHandle;

    /* -------------------- Public Enums ------------------------------------ */
typedef enum dsa_list_type {
    SINGLY_LINKED_LIST,
    DOUBLY_LINKED_LIST,
    CIRCULAR_SINGLY_LINKED_LIST,
    CIRCULAR_DOUBLY_LINKED_LIST,
} dsa_list_type_t;

/* -------------------- Public Structs ---------------------------------- */


/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */

/* Init / Destroy Functions */
LinkedListHandle __cdecl linked_list_initialize(dsa_list_type_t list_type, void *data);
int __cdecl linked_list_delete(LinkedListHandle *handle);
int __cdecl linked_list_mapped_action_on_delete(LinkedListHandle *handle,
                                                void(__cdecl *mapping_fnc)(void *data));

/* Insert Functions */
int __cdecl linked_list_insert_front(LinkedListHandle handle, void *data);
int __cdecl linked_list_insert_back(LinkedListHandle handle, void *data);
int __cdecl linked_list_insert_at(LinkedListHandle handle, uint32_t location, void *data);
int __cdecl linked_list_insert_sorted(LinkedListHandle handle, void *data,
                                      int(__cdecl *cmpfunc)(void *a, void *b));

/* Remove Functions */
int __cdecl linked_list_remove_front(LinkedListHandle handle,
                                     void(__cdecl *fnc_on_removal)(void *data));
int __cdecl linked_list_remove_back(LinkedListHandle handle,
                                    void(__cdecl *fnc_on_removal)(void *data));
int __cdecl linked_list_remove_node(LinkedListHandle handle, void *data,
                                    void(__cdecl *fnc_on_removal)(void *data));
int __cdecl linked_list_remove_at(LinkedListHandle handle, uint32_t location,
                                  void(__cdecl *fnc_on_removal)(void *data));

/* Retrieval Functions*/
void *__cdecl linked_list_get_back(LinkedListHandle handle);
void *__cdecl linked_list_get_at(LinkedListHandle handle, uint32_t location);
void *__cdecl get_front(LinkedListHandle handle);
int32_t __cdecl linked_list_search(LinkedListHandle handle, void *data);
bool __cdecl linked_list_is_empty(LinkedListHandle handle);
int __cdecl linked_list_get_list_size(LinkedListHandle handle);

/* Iterators */
void *__cdecl linked_list_iter_previous(LinkedListHandle handle, void *last_data_ptr);
void *__cdecl linked_list_iter_next(LinkedListHandle handle, void *last_data_ptr);

/* Utility Functions */
int __cdecl linked_list_map_data(LinkedListHandle handle, void(__cdecl *mapping_fnc)(void *data));
void __cdecl linked_list_print(LinkedListHandle handle, void(__cdecl *data_printer)(FILE *, void *), FILE *output_stream);

/* Error Functions */
#ifdef _DSA_ERROR_H_
int __cdecl linked_list_get_error_code(LinkedListHandle handle);
char *__cdecl linked_list_get_error_message(LinkedListHandle handle);
#endif /* _DSA_ERROR_H_ */

#ifdef __cplusplus
    }
#endif


#endif /* _DSA_LINKED_LIST_H_ */