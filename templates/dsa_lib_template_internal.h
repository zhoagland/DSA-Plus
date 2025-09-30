/**
 * @file dsa_template_internal.h
 * @author Zachary Hoagland (zach@zacharyhoagland.com)
 * @brief The purpose of this file is to define privates structs and enums so that they can be exposed for unit
 * testing but not in the public header file
 * @version 0.1
 * @date 202X-XX-XX
 *
 * @copyright Copyright Zachary Hoagland (c) 2025
 *
 */
#ifndef _LIB_TEMPLATE_INTERNAL_H_
#define _LIB_TEMPLATE_INTERNAL_H_


#ifdef __cplusplus
    extern "C" {
#endif


/* -------------------- Private Includes --------------------------------- */
#include "../src/utility/macros/macros.h"
#include "dsa_lib_template.h"

/* -------------------- Private Macros/Defines --------------------------- */
DECLARE_HANDLE(LibraryHandle);


/* -------------------- Private Enums ------------------------------------ */


/* -------------------- Private Structs ---------------------------------- */


/* -------------------- Private Function Declarations -------------------- */
INTERNAL_FUNC int DSA_FUNC library_create(LibraryHandle *handle);
INTERNAL_FUNC int DSA_FUNC library_destroy(LibraryHandle *handle);



#ifdef __cplusplus
    }
#endif


#endif /* _LIB_TEMPLATE_INTERNAL_H_ */