/**
 * @file template.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-04-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _DSA_ERROR_H_
#define _DSA_ERROR_H_


#ifdef __cplusplus
    extern "C" {
#endif


/* -------------------- Public Includes --------------------------------- */

/* -------------------- Public Macros/Defines --------------------------- */

/* -------------------- Public Enums ------------------------------------ */

typedef enum _dsa_glob_error_code {
    SUCCESS = 0,
    INVALID_HANDLE = -1,
} dsa_glob_error_code_t;

/* -------------------- Public Structs ---------------------------------- */
typedef struct _dsa_error_vtbl {
    dsa_glob_error_code_t (*get_error_code)(void *p_error);
    char *(*get_error_message)(void *p_error);
} dsa_error_vtbl_t;

typedef struct _dsa_error_struct {
    const dsa_error_vtbl_t *p_vtbl;
    dsa_glob_error_code_t glob_error_code;
} dsa_error_t;

/* -------------------- Public (global) Vars ---------------------------- */


/* -------------------- Public Function Declarations -------------------- */

void error_ctor(dsa_error_t *const self);

dsa_glob_error_code_t get_error_code(void *error);
char *get_error_message(void *p_error);


#ifdef __cplusplus
    }
#endif


#endif /* _DSA_ERROR_H_ */