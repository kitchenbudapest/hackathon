/* INFO **
** INFO **/

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/rgb_leds.h>
/*  type  : kb_rpi2_sensors_RGBLED
    func  : kb_rpi2_sensors_RGBLED_ini
            kb_rpi2_sensors_RGBLED_fin
            kb_rpi2_sensors_RGBLED_red
            kb_rpi2_sensors_RGBLED_green
            kb_rpi2_sensors_RGBLED_blue
            kb_rpi2_sensors_RGBLED_yellow
            kb_rpi2_sensors_RGBLED_magenta
            kb_rpi2_sensors_RGBLED_cyan
            kb_rpi2_sensors_RGBLED_white
            kb_rpi2_sensors_RGBLED_black */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_RGBLED */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(RGBLED,
                                                           on_enable,
                                                           "RGBLED",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(RGBLED,
                                                           on_disable,
                                                           "RGBLED",
                                                           "onDisable")


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_RGBLED_del
   kbjs_RGBLED_new
   kbjs_RGBLED_type_str
   kbjs_RGBLED_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    RGBLED,
    "RGBLED",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable"),
    3,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-3),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-2),
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Public methods */
/* kbjs_RGBLED_red */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, red, "RGBLED", "red")
/* kbjs_RGBLED_green */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, green, "RGBLED", "green")
/* kbjs_RGBLED_blue */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, blue, "RGBLED", "blue")
/* kbjs_RGBLED_yellow */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, yellow, "RGBLED", "yellow")
/* kbjs_RGBLED_magenta */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, magenta, "RGBLED", "magenta")
/* kbjs_RGBLED_cyan */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, cyan, "RGBLED", "cyan")
/* kbjs_RGBLED_white */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, white, "RGBLED", "white")
/* kbjs_RGBLED_black */
KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(RGBLED, black, "RGBLED", "black")

/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_RGBLED_methods[] =
{
    {"toString", kbjs_RGBLED_instance_str, (duk_idx_t)0},
    {"red"     , kbjs_RGBLED_red         , (duk_idx_t)0},
    {"green"   , kbjs_RGBLED_green       , (duk_idx_t)0},
    {"blue"    , kbjs_RGBLED_blue        , (duk_idx_t)0},
    {"yellow"  , kbjs_RGBLED_yellow      , (duk_idx_t)0},
    {"magenta" , kbjs_RGBLED_magenta     , (duk_idx_t)0},
    {"cyan"    , kbjs_RGBLED_cyan        , (duk_idx_t)0},
    {"white"   , kbjs_RGBLED_white       , (duk_idx_t)0},
    {"black"   , kbjs_RGBLED_black       , (duk_idx_t)0},
    {NULL      , NULL                    , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_RGBLED */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(RGBLED, "RGBLED", 4)
