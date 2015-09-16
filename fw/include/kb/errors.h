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

    /* Utility related error signals */
    kb_ITEM_NOT_IN_CONTAINER,

    /* Pin related error signals */
    kb_INVALID_PIN_ID,
    kb_PIN_ALREADY_USED,
    kb_PIN_DOES_NOT_EXIST,
    kb_TOO_MANY_PINS_USED,

    /* Sensor related error signals */
    kb_PIN_INDEX_IS_OUT_OF_RANGE,

    /* Event related error signals */
    kb_SENSOR_IS_NOT_IN_EVENT,

    /* Context related error signals */
    kb_NO_EVENT_ACTIVATED,
    kb_EVENT_NOT_BOUND_TO_CONTEXT,

} kb_Error;

#endif /* __KB_ERROR_H_8506093783091019__ */