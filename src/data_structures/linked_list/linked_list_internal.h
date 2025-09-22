/**
 * @file linked_list_internal.h
 * @author Zachary Hoagland (zach@zacharyhoagland.com)
 * @brief Internal header for the linked list data structure library.
 * @version 1.0
 * @date 2025-04-03
 *
 * @copyright Copyright Zachary Hoagland (c) 2025
 *
 */
#ifndef _DSA_LINKED_LIST_INTERNAL_H_
#define _DSA_LINKED_LIST_INTERNAL_H_


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------- Public Includes --------------------------------- */
#include "linked_list.h"


#ifdef __DSA_ERROR_HANDLING
    #include "../../utility/error.h"
#endif /* __DSA_ERROR_HANDLING */

/* -------------------- Public Macros/Defines --------------------------- */
#define VALIDATE_HANDLE(HANDLE, RV)                                                            \
    do {                                                                                       \
        if (HANDLE == NULL) return RV;                                                         \
    } while (0)

/* -------------------- Public Enums ------------------------------------ */

#ifdef __DSA_ERROR_HANDLING
typedef enum _dsa_ll_error_codes { LL_ERROR_NONE = 0 } dsa_ll_error_codes_t;
#endif /* __DSA_ERROR_HANDLING */

/* -------------------- Public Structs ---------------------------------- */
#ifdef __DSA_ERROR_HANDLING
typedef struct _dsa_ll_error {
    dsa_error_t          glob_error;
    dsa_ll_error_codes_t error_code;
} dsa_ll_error_t;
#endif /* __DSA_ERROR_HANDLING */

typedef struct _dsa_node {
    void             *data;
    struct _dsa_node *next_node;
    struct _dsa_node *previous_node;
} dsa_node_t;

typedef struct _dsa_linked_list_internal {
    struct LinkedListHandle__ handle;
    dsa_node_t               *head;
    dsa_node_t               *tail;
    dsa_list_type_t           list_type;
    uint32_t                  list_length;
    #ifdef __DSA_ERROR_HANDLING
    dsa_ll_error_t error;
    #endif /* __DSA_ERROR_HANDLING */
} dsa_linked_list_control_block_t;


/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */



#ifdef __cplusplus
}
#endif


#endif /* _DSA_LINKED_LIST_INTERNAL_H_ */