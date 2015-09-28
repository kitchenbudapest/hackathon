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
/*  type  : kb_rpi2_sensors_LED
    func  : kb_rpi2_sensors_LED_ini
            kb_rpi2_sensors_LED_fin
            kb_rpi2_sensors_LED_on
            kb_rpi2_sensors_LED_off
            kb_rpi2_sensors_LED_on_on
            kb_rpi2_sensors_LED_on_off */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_LED */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(LED,
                                                           on_enable,
                                                           "LED",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(LED,
                                                           on_disable,
                                                           "LED",
                                                           "onDisable")
/* on_on
   on_on_setter
   on_on_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(LED,
                                                            on_on,
                                                            "LED",
                                                            "onOn")
/* on_off
   on_off_setter
   on_off_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(LED,
                                                            on_off,
                                                            "LED",
                                                            "onOff")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_LED_del
   kbjs_LED_new
   kbjs_LED_type_str
   kbjs_LED_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    LED,
    "LED",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_on, "onOn")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_off, "onOff"),
    1,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Public methods */
/* kbjs_LED_on */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(LED, on, "LED", "on")
/* kbjs_LED_off */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(LED, off, "LED", "off")

/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_LED_methods[] =
{
    {"toString", kbjs_LED_instance_str, (duk_idx_t)0},
    {"on"      , kbjs_LED_on          , (duk_idx_t)0},
    {"off"     , kbjs_LED_off         , (duk_idx_t)0},
    {NULL      , NULL                 , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_LED */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(LED, "LED", 2)
