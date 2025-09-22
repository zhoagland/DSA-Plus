/**
 * @file macros.h
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
#define DECLARE_HANDLE(name)    struct name##__{int unused;}; typedef struct name##__ *name

/* -------------------- Public Enums ------------------------------------ */


/* -------------------- Public Structs ---------------------------------- */


/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */




#ifdef __cplusplus
    }
#endif


#endif /* _DSA_MACROS_H_ */