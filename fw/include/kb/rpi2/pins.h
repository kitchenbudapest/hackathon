/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_PINS_H_15777440527397069__
#define __KB_RPI2_PINS_H_15777440527397069__


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Pin
            kb_rpi2_Sensor
            kb_rpi2_Event
            kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
const char *const kb_rpi2_PIN_LAYOUT =
    "           +-----+-----+\n"
    "         0 |     |     |  1\n"
    "           +-----+-----+\n"
    "         2 |     |     |  3\n"
    "           +-----+-----+\n"
    "         4 |     |     |  5\n"
    "+---+------+-----+-----+\n"
    "| G |    6 |     |     |  7\n"
    "| P |      +-----+-----+\n"
    "| I |    8 |     |     |  9\n"
    "| O |      +-----+-----+\n"
    "+---+   10 |     |     | 11\n"
    "           +-----+-----+\n"
    "        12 |     |     | 13\n"
    "           +-----+-----+\n"
    "        14 |     |     | 15\n"
    "           +-----+-----+\n"
    "        16 |     |     | 17\n"
    "           +-----+-----+\n"
    "        18 |     |     | 19\n"
    "           +-----+-----+\n"
    "        20 |     |     | 21\n"
    "           +-----+-----+\n"
    "        22 |     |     | 23\n"
    "           +-----+-----+\n"
    "        24 |     |     | 25\n"
    "           +-----+-----+\n"
    "        26 |     |     | 27\n"
    "           +-----+-----+\n"
    "        28 |     |     | 29\n"
    "           +-----+-----+\n"
    "        30 |     |     | 31\n"
    "           +-----+-----+\n"
    "        32 |     |     | 33\n"
    "           +-----+-----+\n"
    "        34 |     |     | 35\n"
    "           +-----+-----+\n"
    "        36 |     |     | 37\n"
    "           +-----+-----+\n"
    "        38 |     |     | 39\n"
    "           +-----+-----+\n";


/*----------------------------------------------------------------------------*/
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG3_IS_NULL:
        if sensor argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of the new Pin object failed */
kb_Error
kb_rpi2_Pin_new(kb_rpi2_Pin    **const self,
                kb_rpi2_PinId          pin_id,
                kb_rpi2_Sensor  *const sensor);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_del(kb_rpi2_Pin **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_reset(kb_rpi2_Pin *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_set_high(kb_rpi2_Pin *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_set_low(kb_rpi2_Pin *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if on_high is a NULL pointer */
kb_Error
kb_rpi2_Pin_bind_on_high(kb_rpi2_Pin *const self,
                         kb_Error   (*on_high)(kb_rpi2_Pin     *const,
                                               kb_rpi2_Sensor  *const,
                                               kb_rpi2_Event   *const,
                                               kb_rpi2_Context *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_unbind_on_high(kb_rpi2_Pin *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if on_low is a NULL pointer */
kb_Error
kb_rpi2_Pin_bind_on_low(kb_rpi2_Pin *const self,
                        kb_Error   (*on_low)(kb_rpi2_Pin     *const,
                                             kb_rpi2_Sensor  *const,
                                             kb_rpi2_Event   *const,
                                             kb_rpi2_Context *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Pin_unbind_on_low(kb_rpi2_Pin *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if sensor is a pointer to NULL
    kb_ARG3_IS_NULL:
        if event is a pointer to NULL
    kb_ARG4_IS_NULL:
        if event is a pointer to NULL */
kb_Error
kb_rpi2_Pin_callback_args(kb_rpi2_Pin      *const  self,
                          kb_rpi2_Sensor  **const sensor,
                          kb_rpi2_Event   **const event,
                          kb_rpi2_Context **const context);


#endif /* __KB_RPI2_PINS_H_15777440527397069__ */
