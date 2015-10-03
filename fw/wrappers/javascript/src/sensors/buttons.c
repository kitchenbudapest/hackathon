/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/buttons.h>
/*  type  : kb_rpi2_sensors_Button
    func  : kb_rpi2_sensors_Button_ini
            kb_rpi2_sensors_Button_fin
            kb_rpi2_sensors_Button_on_press
            kb_rpi2_sensors_Button_on_release */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_Button */
#include "include/sensors/common.h"
/*  macro : KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C
            KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS
            KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER
            KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER
            KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER */


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
/* on_enable
   on_enable_setter
   on_enable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(Button,
                                                           on_enable,
                                                           "Button",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(Button,
                                                           on_disable,
                                                           "Button",
                                                           "onDisable")
/* on_press
   on_press_setter
   on_press_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(Button,
                                                            on_press,
                                                            "Button",
                                                            "onPress")
/* on_release
   on_release_setter
   on_release_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(Button,
                                                            on_release,
                                                            "Button",
                                                            "onRelease")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_Button_del
   kbjs_Button_new
   kbjs_Button_type_str
   kbjs_Button_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    Button,
    "Button",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_press, "onPress")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_release, "onRelease"),
    1,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))


/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_Button_methods[] =
{
    {"toString", kbjs_Button_instance_str, (duk_idx_t)0},
    {NULL      , NULL                    , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_Button */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(Button, "Button", 2)
