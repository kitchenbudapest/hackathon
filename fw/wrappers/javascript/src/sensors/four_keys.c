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
/*  type  : kb_rpi2_sensors_FourKeys
    func  : kb_rpi2_sensors_FourKeys_ini
            kb_rpi2_sensors_FourKeys_fin
            kb_rpi2_sensors_FourKeys_on_key_1
            kb_rpi2_sensors_FourKeys_on_key_2
            kb_rpi2_sensors_FourKeys_on_key_3
            kb_rpi2_sensors_FourKeys_on_key_4 */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_FourKeys */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                           on_enable,
                                                           "FourKeys",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                           on_disable,
                                                           "FourKeys",
                                                           "onDisable")
/* on_key_1
   on_key_1_setter
   on_key_1_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                            on_key_1,
                                                            "FourKeys",
                                                            "onKey1")
/* on_key_2
   on_key_2_setter
   on_key_2_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                            on_key_2,
                                                            "FourKeys",
                                                            "onKey2")
/* on_key_3
   on_key_3_setter
   on_key_3_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                            on_key_3,
                                                            "FourKeys",
                                                            "onKey3")
/* on_key_4
   on_key_4_setter
   on_key_4_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(FourKeys,
                                                            on_key_4,
                                                            "FourKeys",
                                                            "onKey4")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_FourKeys_del
   kbjs_FourKeys_new
   kbjs_FourKeys_type_str
   kbjs_FourKeys_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    FourKeys,
    "FourKeys",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_key_1, "onKey1")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_key_2, "onKey2")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_key_3, "onKey3")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_key_4, "onKey4"),
    5,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-5),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-4),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-3),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-2),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))

/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_FourKeys_methods[] =
{
    {"toString", kbjs_FourKeys_instance_str, (duk_idx_t)0},
    {NULL      , NULL                      , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_FourKeys */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(FourKeys, "FourKeys", 6)
