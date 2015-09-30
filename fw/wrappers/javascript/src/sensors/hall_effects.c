/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/hall_effects.h>
/*  type  : kb_rpi2_sensors_HallEffect
    func  : kb_rpi2_sensors_HallEffect_ini
            kb_rpi2_sensors_HallEffect_fin
            kb_rpi2_sensors_HallEffect_on_magnetize
            kb_rpi2_sensors_HallEffect_on_demagnetize */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  type  : kbjs_HallEffect */
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
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(HallEffect,
                                                           on_enable,
                                                           "HallEffect",
                                                           "onEnable")
/* on_disable
   on_disable_setter
   on_disable_getter */
KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(HallEffect,
                                                           on_disable,
                                                           "HallEffect",
                                                           "onDisable")
/* on_magnetize
   on_magnetize_setter
   on_magnetize_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(HallEffect,
                                                            on_magnetize,
                                                            "HallEffect",
                                                            "onMagnetize")
/* on_demagnetize
   on_demagnetize_setter
   on_demagnetize_getter */
KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(HallEffect,
                                                            on_demagnetize,
                                                            "HallEffect",
                                                            "onDemagnetize")

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Internal methods */
/* kbjs_HallEffect_del
   kbjs_HallEffect_new
   kbjs_HallEffect_type_str
   kbjs_HallEffect_instance_str */
KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(
    HallEffect,
    "HallEffect",
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_enable, "onEnable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_disable, "onDisable")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_magnetize, "onMagnetize")
    KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(on_demagnetize, "onDemagnetize"),
    1,
    KBJS_SENSORS_COMMON_PINS_ARGUMENTS(-1))


/*----------------------------------------------------------------------------*/
/* Methods list */
static const duk_function_list_entry kbjs_HallEffect_methods[] =
{
    {"toString", kbjs_HallEffect_instance_str, (duk_idx_t)0},
    {NULL      , NULL                        , (duk_idx_t)0},
};

/*----------------------------------------------------------------------------*/
/* kbjs_register_HallEffect */
KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(HallEffect, "HallEffect", 2)
