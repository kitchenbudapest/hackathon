/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_ERROR_H_8506093783091019__
#define __KB_ERROR_H_8506093783091019__

/*----------------------------------------------------------------------------*/
typedef enum
{
    /* Generic error signals */
    kb_OKAY,
    kb_FAIL,

    /* Function call related error signals */
    kb_SELF_IS_NULL,
    kb_ARG1_IS_NULL,
    kb_ARG2_IS_NULL,
    kb_ARG3_IS_NULL,
    kb_ARG4_IS_NULL,
    kb_ARG5_IS_NULL,

    /* Memory management related error signals */
    kb_ALLOC_FAIL,

    /* Containers and collections related error signals */
    //kb_INDEX_OUT_OF_RANGE,

    /* Device related error signals */
    kb_PIN_ALREADY_USED,
    kb_INVALID_PIN_ID,

} kb_Error;

#endif /* __KB_ERROR_H_8506093783091019__ */
