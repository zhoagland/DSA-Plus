/**
 * @file dsa_macros.h
 * @author Zachary Hoagland (zach@zacharyhoagland.com)
 * @brief Header file for common macros used in the library
 * @version 1.0
 * @date 2025-04-03
 *
 * @copyright Copyright Zachary Hoagland (c) 2025
 *
 */
#ifndef _DSA_MACROS_H_
#define _DSA_MACROS_H_


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------- Public Includes --------------------------------- */


/* -------------------- Public Macros/Defines --------------------------- */

/** Macro to create handle (opaque ptr type) same way used my windows */
#define DECLARE_HANDLE(name)                                                                       \
    struct name##__ {                                                                              \
        int unused;                                                                                \
    };                                                                                             \
    typedef struct name##__ *name

// This macro sets private functions as either static or global based on whether or not
// They need to be exposed for unit testing.
#ifdef __UNIT_TESTING__
    #define INTERNAL_FUNC
#else
    #define INTERNAL_FUNC static inline
#endif

/** Macro for ABI definition */
#define DSA_FUNC __cdecl


/* -------------------- Public Enums ------------------------------------ */


/* -------------------- Public Structs ---------------------------------- */


/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */


#ifdef __cplusplus
}
#endif


#endif /* _DSA_MACROS_H_ */