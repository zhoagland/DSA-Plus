/**
* @file lib_template.c
* @author Zachary Hoagland (zach@zacharyhoagland.com)
* @brief
* @version 0.1
* @date 202X-XX-XX
*
* @copyright Copyright (c) 2025
*
*/

/* -------------------- Private Includes ------------------------------------------- */
#include "dsa_lib_template.h"
#include "dsa_lib_template_internal.h" // This header file has all the public includes for the module
#include <stdatomic.h>
#include <stdbool.h>

// Build condition for linking LabWindowsCVI header files and using their runtime.
// Only relevant when targeting compatibility with that build system.
#ifndef __CVI_LIB__
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
#else
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdio.h"
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdint.h"
    #include "C:\Program Files (x86)\National Instruments\CVI2020\include\ansi\stdlib.h"
#endif  // !_CVI_LIB_

/* -------------------- Private Macros/Defines ------------------------------------- */




/* -------------------- Private Enums ---------------------------------------------- */
typedef enum _lib_err_msg{
    LIB_NO_ERR,
    LIB_ERR_MSG,
    LIB_ERR_MSG_CNT
} lib_err_msg_t;

/* -------------------- Private Structs -------------------------------------------- */

typedef struct _library_iterator {
    atomic_bool has_next;
    void *next;
} library_iterator_t;

typedef struct _library_internal {
    LibraryHandle handle;
    _Atomic(lib_err_msg_t) error_code;
    _Atomic(library_iterator_t) iterator;
    void *other_data;
} library_internal_t;

/* -------------------- Private (static) Vars -------------------------------------- */
const char *library_err_messages[LIB_ERR_MSG_CNT] = {
    "No Error",
    "Error Message"
};

/* -------------------- Private (static) Function Declarations --------------------- */


/* -------------------- Public (global) Vars --------------------------------------- */


/* -------------------- Private and Public Function Definitions -------------------- */

INTERNAL_FUNC int DSA_FUNC library_create(LibraryHandle *handle) {
    if (!handle) {
        return -LIB_ERR_MSG; /* invalid parameter */
    }

    library_internal_t *internal_handle = (library_internal_t *)calloc(1, sizeof(library_internal_t));

    if (!internal_handle) {
        /* allocation failed */
        return -LIB_ERR_MSG;
    }

    /* set the opaque handle to point to our internal struct */
    *handle = (LibraryHandle)internal_handle;

    /* initialize atomics and fields */
    atomic_init(&internal_handle->error_code, LIB_NO_ERR);

    /* initialize iterator: its has_next is an atomic_bool, so init it first */
    library_iterator_t it = {0};
    atomic_init(&it.has_next, false);
    it.next = NULL;
    atomic_init(&internal_handle->iterator, it);

    internal_handle->other_data = NULL;

    return 0;
}

INTERNAL_FUNC int DSA_FUNC library_destroy(LibraryHandle *handle) {
    if (!handle || !*handle) {
        return -LIB_ERR_MSG; /* invalid parameter */
    }

    library_internal_t *internal_handle = (library_internal_t *)(*handle);

    // Free any other dynamically allocated data here
    if (internal_handle->other_data) {
        free(internal_handle->other_data);
        internal_handle->other_data = NULL;
    }

    // Finally, free the internal handle itself
    free(internal_handle);
    *handle = NULL;

    return 0;
}

INTERNAL_FUNC int DSA_FUNC lib_get_error_code(LibraryHandle handle) {
    if (!handle) {
        return 0;
    }

    /* read the atomic error code safely */
    lib_err_msg_t code = atomic_load(&((library_internal_t*)handle)->error_code);
    return (int)code * -1;
}

INTERNAL_FUNC const char* DSA_FUNC lib_get_error_message(int error_code) {
    int idx = -error_code;
    if (idx < 0 || idx >= LIB_ERR_MSG_CNT) {
        return "Unknown Error";
    }
    return library_err_messages[idx];
}
