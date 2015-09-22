/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include jemalloc headers */
#include <jemalloc/jemalloc.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    func  : kb_Error_str */
#include <kb/rpi2/sensors/leds.h>
/*  type  : kb_rpi2_sensors_LED
            kb_rpi2_sensors_LED_ini
            kb_rpi2_sensors_LED_fin
            kb_rpi2_sensors_LED_on
            kb_rpi2_sensors_LED_off */
#include "include/types.h"
/*  macro : KBJS_TYPES_STASH_KEY_LENGTH
    type  : kbjs_Context
            kbjs_Event
            kbjs_LED
    func  : kbjs_get_stash_key */

/*----------------------------------------------------------------------------*/
/* Instance methods */
static duk_ret_t
kbjs_LED_new(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.sensors.LED_initialize()";

    /* If function not called as a constructor */
    if (!duk_is_constructor_call(context))
        duk_error(context,
                  (duk_errcode_t)kbjs_InvocationError,
                  kbjs_Error_fmt(kbjs_InvocationError),
                  FUNC_NAME);

    /* Create new Context instance */
    kbjs_LED *kb_led;
    if (!(kb_led = malloc(sizeof(kbjs_LED))))
        duk_error(context,
                  (duk_errcode_t)kbjs_AllocationError,
                  kbjs_Error_fmt(kbjs_AllocationError),
                  FUNC_NAME);

    /* Initialze instance as kibu Context */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_ini((kb_rpi2_Context *const)kb_led)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_del(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.LED_finalize()";

    /* STACK: [this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_LED *kb_led = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_sensors_LED_fin((kb_rpi2_sensors_LED *const)kb_led)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);

    /* Deallocate instance */
    free(kb_led);

    /* STACK: [] */
    duk_pop_2(context);
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_type_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_FUNC("kb.rpi2.sensors.LED"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_instance_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_OBJ("kb.rpi2.sensors.LED"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_on(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.sensors.LED.on()";

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* STACK: [args..., this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_LED *kb_led = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_sensors_LED_on((kb_rpi2_sensors_LED *const)kb_led)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);

    /* STACK: [args...] */
    duk_pop_2(context);
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_off(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.sensors.LED.on()";

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* STACK: [args..., this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_LED *kb_led = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_sensors_LED_off((kb_rpi2_sensors_LED *const)kb_led)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);

    /* STACK: [args...] */
    duk_pop_2(context);
    return (duk_ret_t)0;
}


/*----------------------------------------------------------------------------*/
static const duk_function_list_entry kbjs_LED_methods[] =
{
    {"toString", kbjs_LED_instance_str, (duk_idx_t)0},
    {"on"      , kbjs_LED_on          , (duk_idx_t)0},
    {"off"     , kbjs_LED_off         , (duk_idx_t)0},
    {NULL      , NULL                 , (duk_idx_t)0},
};


/*----------------------------------------------------------------------------*/
void
kbjs_register_LED(duk_context *context)
{
    /* Get kb.rpi2.sensors object */
    /* STACK: [global] */
    duk_push_global_object(context);
    /* STACK: [global, kb] */
    duk_get_prop_string(context, (duk_idx_t)-1, "kb");
    /* STACK: [global, kb, rpi] */
    duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");
    /* STACK: [global, kb, rpi, sensors, sensors] */
    duk_get_prop_string(context, (duk_idx_t)-1, "sensors");

    /* Create kb.rpi2.sensors.LED constructor */
    /* STACK: [global, kb, rpi, sensors, "LED"] */
    duk_push_string(context, "LED");
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new()] */
    duk_push_c_function(context, kbjs_LED_new, (duk_idx_t)0);

    /* Create kb.rpi2.Context.toString */
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "toString"] */
    duk_push_string(context, "toString");
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "toString", toString()] */
    duk_push_c_function(context, kbjs_LED_type_str, (duk_idx_t)1);
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new()] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create kb.rpi2.Context.prototype */
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "prototype"] */
    duk_push_string(context, "prototype");
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "prototype", {}] */
    duk_push_object(context);
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "prototype", {f...}] */
    duk_put_function_list(context, (duk_idx_t)-1, kbjs_LED_methods);

    /* Set prototype */
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new()] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* Set constructor */
    /* STACK: [global, kb, rpi, sensors] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Clean up */
    /* STACK: [] */
    duk_pop_n(context, (duk_idx_t)4);
}