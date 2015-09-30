/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/leds.h>
/*  type  : kb_rpi2_sensors_UltrasonicSensor
    func  : kb_rpi2_sensors_UltrasonicSensor_ini
            kb_rpi2_sensors_UltrasonicSensor_fin
            kb_rpi2_sensors_UltrasonicSensor_measure */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_UltrasonicSensor */
#include "include/sensors/common.h"
/*  macro : KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C
            KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS
            KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER
            KBJS_SENSORS_COMMON_NUMBER_RETURNED_SIMPLE_METHODS_WRAPPER
            KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER
            KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER */


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
/* on_enable
   on_enable_setter
   on_enable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(UltrasonicSensor,
                                                           on_enable,
                                                           "UltrasonicSensor",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(UltrasonicSensor,
                                                           on_disable,
                                                           "UltrasonicSensor",
                                                           "onDisable")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_UltrasonicSensor_del
   kbjs_UltrasonicSensor_new
   kbjs_UltrasonicSensor_type_str
   kbjs_UltrasonicSensor_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    UltrasonicSensor,
    "UltrasonicSensor",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable"),
    2,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-2),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Public methods */
/* kbjs_UltrasonicSensor_measure */
KBJS_SENSORS_COMMON_NUMBER_RETURNED_SIMPLE_METHODS_WRAPPER(
    UltrasonicSensor,
    measure,
    "UltrasonicSensor",
    "measure")

/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_UltrasonicSensor_methods[] =
{
    {"toString", kbjs_UltrasonicSensor_instance_str, (duk_idx_t)0},
    {"measure" , kbjs_UltrasonicSensor_measure     , (duk_idx_t)0},
    {NULL      , NULL                              , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_UltrasonicSensor */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(UltrasonicSensor, "UltrasonicSensor", 3)
