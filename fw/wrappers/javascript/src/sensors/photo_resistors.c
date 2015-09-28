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
/*  type  : kb_rpi2_sensors_PhotoResistor
    func  : kb_rpi2_sensors_PhotoResistor_ini
            kb_rpi2_sensors_PhotoResistor_fin
            kb_rpi2_sensors_PhotoResistor_on_light
            kb_rpi2_sensors_PhotoResistor_on_dark */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_PhotoResistor */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(PhotoResistor,
                                                           on_enable,
                                                           "PhotoResistor",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(PhotoResistor,
                                                           on_disable,
                                                           "PhotoResistor",
                                                           "onDisable")
/* on_light
   on_light_setter
   on_light_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(PhotoResistor,
                                                            on_light,
                                                            "PhotoResistor",
                                                            "onLight")
/* on_dark
   on_dark_setter
   on_dark_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(PhotoResistor,
                                                            on_dark,
                                                            "PhotoResistor",
                                                            "onDark")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_PhotoResistor_del
   kbjs_PhotoResistor_new
   kbjs_PhotoResistor_type_str
   kbjs_PhotoResistor_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    PhotoResistor,
    "PhotoResistor",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_light, "onLight")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_dark, "onDark"),
    1,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))


/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_PhotoResistor_methods[] =
{
    {"toString", kbjs_PhotoResistor_instance_str, (duk_idx_t)0},
    {NULL      , NULL                           , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_PhotoResistor */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(PhotoResistor, "PhotoResistor", 2)
