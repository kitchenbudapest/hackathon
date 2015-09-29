/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/photo_resistors.h>
/*  type  : kb_rpi2_sensors_MotionSensor
    func  : kb_rpi2_sensors_MotionSensor_ini
            kb_rpi2_sensors_MotionSensor_fin
            kb_rpi2_sensors_MotionSensor_on_motion
            kb_rpi2_sensors_MotionSensor_on_still */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_MotionSensor */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(MotionSensor,
                                                           on_enable,
                                                           "MotionSensor",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(MotionSensor,
                                                           on_disable,
                                                           "MotionSensor",
                                                           "onDisable")
/* on_motion
   on_motion_setter
   on_motion_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(MotionSensor,
                                                            on_motion,
                                                            "MotionSensor",
                                                            "onMotion")
/* on_still
   on_still_setter
   on_still_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(MotionSensor,
                                                            on_still,
                                                            "MotionSensor",
                                                            "onStill")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_MotionSensor_del
   kbjs_MotionSensor_new
   kbjs_MotionSensor_type_str
   kbjs_MotionSensor_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    MotionSensor,
    "MotionSensor",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_motion, "onMotion")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_still, "onStill"),
    1,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))


/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_MotionSensor_methods[] =
{
    {"toString", kbjs_MotionSensor_instance_str, (duk_idx_t)0},
    {NULL      , NULL                          , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_MotionSensor */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(MotionSensor, "MotionSensor", 2)
