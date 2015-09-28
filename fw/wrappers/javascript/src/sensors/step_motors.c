/* INFO **
** INFO **/

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/four_keys.h>
/*  type  : kb_rpi2_sensors_StepMotor
    func  : kb_rpi2_sensors_StepMotor_ini
            kb_rpi2_sensors_StepMotor_fin
            kb_rpi2_sensors_StepMotor_rotate
            kb_rpi2_sensors_StepMotor_rotate_degree
            kb_rpi2_sensors_StepMotor_rotate_radian */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_StepMotor */
#include "include/sensors/common.h"
/*  macro : KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C
            KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS
            KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER
            KBJS_SENSORS_COMMON_SINGLE_NUMBER_METHODS_WRAPPER
            KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER
            KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER */


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
/* on_enable
   on_enable_setter
   on_enable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(StepMotor,
                                                           on_enable,
                                                           "StepMotor",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(StepMotor,
                                                           on_disable,
                                                           "StepMotor",
                                                           "onDisable")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_StepMotor_del
   kbjs_StepMotor_new
   kbjs_StepMotor_type_str
   kbjs_StepMotor_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    StepMotor,
    "StepMotor",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable"),
    4,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-4),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-3),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-2),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Public methods */
/* kbjs_StepMotor_rotate */
KBJS_SENSORS_COMMON_SINGLE_NUMBER_METHODS_WRAPPER(StepMotor,
                                                  rotate,
                                                  "StepMotor",
                                                  "rotate")
/* kbjs_StepMotor_rotate_degree */
KBJS_SENSORS_COMMON_SINGLE_NUMBER_METHODS_WRAPPER(StepMotor,
                                                  rotate_degree,
                                                  "StepMotor",
                                                  "rotateDegree")
/* kbjs_StepMotor_rotate_radian */
KBJS_SENSORS_COMMON_SINGLE_NUMBER_METHODS_WRAPPER(StepMotor,
                                                  rotate_radian,
                                                  "StepMotor",
                                                  "rotateRadian")

/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_StepMotor_methods[] =
{
    {"toString"    , kbjs_StepMotor_instance_str , (duk_idx_t)0},
    {"rotate"      , kbjs_StepMotor_rotate       , (duk_idx_t)1},
    {"rotateDegree", kbjs_StepMotor_rotate_degree, (duk_idx_t)1},
    {"rotateRadian", kbjs_StepMotor_rotate_radian, (duk_idx_t)1},
    {NULL          , NULL                        , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_StepMotor */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(StepMotor, "StepMotor", 5)
