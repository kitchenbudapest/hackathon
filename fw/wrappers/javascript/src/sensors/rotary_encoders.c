/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/rotary_encoders.h>
/*  type  : kb_rpi2_sensors_RotaryEncoder
    func  : kb_rpi2_sensors_RotaryEncoder_ini
            kb_rpi2_sensors_RotaryEncoder_fin
            kb_rpi2_sensors_RotaryEncoder_on_click
            kb_rpi2_sensors_RotaryEncoder_on_rotate_clock_wise
            kb_rpi2_sensors_RotaryEncoder_on_rotate_counter_clock_wise */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_RotaryEncoder */
#include "include/sensors/common.h"
/*  macro : KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C
            KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS
            KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER
            KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER
            KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER
            KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER */


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
/* on_enable
   on_enable_setter
   on_enable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(RotaryEncoder,
                                                           on_enable,
                                                           "RotaryEncoder",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(RotaryEncoder,
                                                           on_disable,
                                                           "RotaryEncoder",
                                                           "onDisable")
/* on_click
   on_click_setter
   on_click_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(RotaryEncoder,
                                                            on_click,
                                                            "RotaryEncoder",
                                                            "onClick")
/* on_rotate_clock_wise
   on_rotate_clock_wise_setter
   on_rotate_clock_wise_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(
    RotaryEncoder,
    on_rotate_clock_wise,
    "RotaryEncoder",
    "onRotateClockWise")
/* on_rotate_counter_clock_wise
   on_rotate_counter_clock_wise_setter
   on_rotate_counter_clock_wise_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(
    RotaryEncoder,
    on_rotate_counter_clock_wise,
    "RotaryEncoder",
    "onRotateCounterClockWise")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_RotaryEncoder_del
   kbjs_RotaryEncoder_new
   kbjs_RotaryEncoder_type_str
   kbjs_RotaryEncoder_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    RotaryEncoder,
    "RotaryEncoder",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_click, "onClick")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_rotate_clock_wise,
                                            "onRotateClockWise")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_rotate_counter_clock_wise,
                                            "onRotateCounterClockWise"),
    3,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-3),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-2),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))


/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_RotaryEncoder_methods[] =
{
    {"toString", kbjs_RotaryEncoder_instance_str, (duk_idx_t)0},
    {NULL      , NULL                           , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_RotaryEncoder */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(RotaryEncoder, "RotaryEncoder", 4)
