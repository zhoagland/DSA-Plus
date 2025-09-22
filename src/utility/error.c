/**
* @file error.c
* @author Zach Hoagland(zach@zacharyhoagland.com)
* @brief
* @version 0.1
* @date 2025-04-03
*
* @copyright Copyright (c) 2025
*
*/
/* -------------------- Private Includes ------------------------------------------- */
#include "error.h"

/* -------------------- Private Macros/Defines ------------------------------------- */


/* -------------------- Private Enums ---------------------------------------------- */


/* -------------------- Private Structs -------------------------------------------- */


/* -------------------- Private (static) Vars -------------------------------------- */
const char *global_error_message[] = {
    "Error Message",
};

/* -------------------- Private (static) Function Declarations --------------------- */
static dsa_glob_error_code_t get_error_code_(void *p_error);
static char *get_error_message_(void *p_error);

/* -------------------- Public (global) Vars --------------------------------------- */


/* -------------------- Private and Public Function Definitions -------------------- */
void error_ctor(dsa_error_t *const self) {
    static const dsa_error_vtbl_t vtbl = {
        .get_error_code = &get_error_code_,
        .get_error_message = &get_error_message_
    };

    self->p_vtbl = &vtbl;
}

dsa_glob_error_code_t get_error_code_(void *p_error) {
    dsa_error_t *const error = ((dsa_error_t*)p_error);
    return (error->glob_error_code)*-1;
}


dsa_glob_error_code_t get_error_code(void *p_error) {
    dsa_error_t *const self = ((dsa_error_t*)p_error);
    return self->p_vtbl->get_error_code(p_error);
}

char *get_error_message(void *p_error) {
    dsa_error_t *const self = ((dsa_error_t*)p_error);

    return self->p_vtbl->get_error_message(p_error);
}

char *get_error_message_(void *p_error) {
    return global_error_message[get_error_code(p_error)];
}