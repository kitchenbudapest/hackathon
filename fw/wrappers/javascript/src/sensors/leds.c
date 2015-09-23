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
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    func  : kb_rpi2_Sensor_bind_on_enable
            kb_rpi2_Sensor_bind_on_disable */
#include <kb/rpi2/sensors/leds.h>
/*  type  : kb_rpi2_sensors_LED
            kb_rpi2_sensors_LED_ini
            kb_rpi2_sensors_LED_fin
            kb_rpi2_sensors_LED_on
            kb_rpi2_sensors_LED_off */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/keys.h"
/*  macro : KBJS_NATIVE_OBJ
            KBJS_NATIVE_FUNC
            KBJS_INSTANCE_PTR */
#include "include/errors.h"
/*  const : kbjs_InternalError
            kbjs_InvocationError
            kbjs_PropertyTypeError
            kbjs_AllocationError
    func  : kbjs_Error_fmt */
#include "include/pin_ids.h"
/*  const : kbjs_PIN_ID_PROTO_STASH_KEY */
#include "include/types.h"
/*  macro : KBJS_TYPES_STASH_KEY_LENGTH
    type  : kbjs_Context
            kbjs_Event
            kbjs_LED
    func  : kbjs_get_stash_key */
#include "include/js_types.h"
/*  func  : kbjs_js_types_str */


/*----------------------------------------------------------------------------*/
/* Forward declarations */
static duk_ret_t
kbjs_LED_new(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_del(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_type_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_instance_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_on(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_off(duk_context *context);


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
#define CALLBACK_WRAPPER(C_NAME, JS_NAME)                                      \
    static kb_Error                                                            \
    C_NAME(kb_rpi2_Sensor  *const kb_sensor,                                   \
           kb_rpi2_Event   *const kb_event,                                    \
           kb_rpi2_Context *const kb_context)                                  \
    {                                                                          \
        /* STACK: [...] */                                                     \
        duk_context *context = ((kbjs_LED *const)kb_sensor)->js_context;       \
                                                                               \
        /* STACK: [..., stash] */                                              \
        duk_push_heap_stash(context);                                          \
                                                                               \
        /* STACK: [..., stash, ""] */                                          \
        duk_push_string(context, ((kbjs_LED *const)kb_sensor)->js_stash_key);  \
        /* STACK: [..., stash, this] */                                        \
        duk_get_prop(context, (duk_idx_t)-2);                                  \
                                                                               \
        /* Get callback function-key*/                                         \
        /* STACK: [..., stash, this, "_JS_NAME"] */                            \
        duk_push_string(context, "_" JS_NAME);                                 \
        /* Set first argument */                                               \
        /* STACK: [..., stash, this, "_JS_NAME", this] */                      \
        duk_dup(context, (duk_idx_t)-2);                                       \
                                                                               \
        /* Get/set second argument */                                          \
        /* STACK: [..., stash, this, "_JS_NAME", this, event] */               \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-1,                                     \
                            ((kbjs_Event *const)kb_event)->js_stash_key);      \
                                                                               \
        /* Get/set third argument */                                           \
        /* STACK: [..., stash, this, "_JS_NAME", this, event, context] */      \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-2,                                     \
                            ((kbjs_Context *const)kb_context)->js_stash_key);  \
                                                                               \
        /* Invoke callback */                                                  \
        /* STACK: [..., stash, this, result] */                                \
        duk_call_prop(context, (duk_idx_t)-5, (duk_idx_t)3);                   \
                                                                               \
        kb_Error error = kb_OKAY;                                              \
        /* STACK: [..., stash, this, bool(result)] */                          \
        if (duk_to_boolean(context, (duk_idx_t)-1))                            \
            error = kb_FAIL;                                                   \
                                                                               \
        /* STACK: [...] */                                                     \
        duk_pop_3(context);                                                    \
        return error;                                                          \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create callback wrappers */
CALLBACK_WRAPPER(on_enable,  "onEnable")
CALLBACK_WRAPPER(on_disable, "onDisable")
#undef CALLBACK_WRAPPER


/*----------------------------------------------------------------------------*/
/* Callback getters */
#define CALLBACK_GETTER(C_NAME, JS_NAME)                                       \
    static duk_ret_t                                                           \
    C_NAME##_getter(duk_context *context)                                      \
    {                                                                          \
        /* STACK: [..., this] */                                               \
        duk_push_this(context);                                                \
        /* STACK: [..., this, value] */                                        \
        duk_get_prop_string(context, (duk_idx_t)-1, "_" JS_NAME);              \
        return (duk_ret_t)1;                                                   \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create getter */
CALLBACK_GETTER(on_enable,  "onEnable")
CALLBACK_GETTER(on_disable, "onDisable")
#undef CALLBACK_GETTER


/*----------------------------------------------------------------------------*/
#define CALLBACK_SETTER(C_NAME, JS_NAME)                                       \
    static duk_ret_t                                                           \
    C_NAME##_setter(duk_context *context)                                      \
    {                                                                          \
        static const char *FUNC_NAME = "kb.rpi2.sensors.LED."                  \
                                       JS_NAME "_setter";                      \
        kb_Error kb_error;                                                     \
        kbjs_LED *kb_led;                                                      \
        /* STACK: [..., arg] */                                                \
        /* If argument is undefined */                                         \
        if (duk_is_undefined(context, (duk_idx_t)-1))                          \
        {                                                                      \
            /* If the given value is something else */                         \
            /* STACK: [..., arg, this] */                                      \
            duk_push_this(context);                                            \
                                                                               \
            /* STACK: [..., arg, this, ""] */                                  \
            duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);    \
            /* STACK: [..., arg, this, void*] */                               \
            kb_led = duk_get_pointer(context, (duk_idx_t)-1);                  \
                                                                               \
            /* Unset callback */                                               \
            if ((kb_error = kb_rpi2_Sensor_unbind_##C_NAME(                    \
                    (kb_rpi2_Sensor *const)kb_led)))                           \
                        duk_error(context,                                     \
                                  (duk_errcode_t)kbjs_InternalError,           \
                                  kbjs_Error_fmt(kbjs_InternalError),          \
                                  kb_Error_str(kb_error),                      \
                                  FUNC_NAME);                                  \
        }                                                                      \
        /* If argument is a function */                                        \
        else if (duk_is_callable(context, (duk_idx_t)-1))                      \
        {                                                                      \
            /* If the given value is something else */                         \
            /* STACK: [..., arg, this] */                                      \
            duk_push_this(context);                                            \
                                                                               \
            /* STACK: [..., arg, this, ""] */                                  \
            duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);    \
            /* STACK: [..., arg, this, void*] */                               \
            kb_led = duk_get_pointer(context, (duk_idx_t)-1);                  \
                                                                               \
            /* Unset callback */                                               \
            if ((kb_error = kb_rpi2_Sensor_bind_##C_NAME(                      \
                    (kb_rpi2_Sensor *const)kb_led,                             \
                    C_NAME)))                                                  \
                        duk_error(context,                                     \
                                  (duk_errcode_t)kbjs_InternalError,           \
                                  kbjs_Error_fmt(kbjs_InternalError),          \
                                  kb_Error_str(kb_error),                      \
                                  FUNC_NAME);                                  \
        }                                                                      \
        /* If argument is something else */                                    \
        else                                                                   \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_PropertyTypeError,                   \
                      kbjs_Error_fmt(kbjs_PropertyTypeError),                  \
                      FUNC_NAME,                                               \
                      kbjs_js_types_str(duk_get_type(context, (duk_idx_t)-1)));\
                                                                               \
        /* Store value */                                                      \
        /* STACK: [..., arg, this] */                                          \
        duk_pop(context);                                                      \
        /* STACK: [..., this, arg] */                                          \
        duk_swap_top(context, (duk_idx_t)-2);                                  \
        /* STACK: [..., this] */                                               \
        duk_put_prop_string(context, (duk_idx_t)-2, "_" JS_NAME);              \
        /* STACK: [...] */                                                     \
        duk_pop(context);                                                      \
        return (duk_ret_t)0;                                                   \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create setter */
CALLBACK_SETTER(on_enable,  "onEnable")
CALLBACK_SETTER(on_disable, "onDisable")
#undef CALLBACK_SETTER



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


    /* STACK: [..., arg1, arg2, kb] */
    duk_get_global_string(context, "kb");
    /* STACK: [..., arg1, arg2, kb, rpi2] */
    duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");
    /* STACK: [..., arg1, arg2, kb, rpi2, Event] */
    duk_get_prop_string(context, (duk_idx_t)-1, "Event");

    /* If first argument is not an instance of kb.rpi2.Event */
    if (!duk_instanceof(context, (duk_idx_t)-5, (duk_idx_t)-1))
        duk_error(context,
                  (duk_errcode_t)kbjs_ArgumentTypeError,
                  kbjs_Error_fmt(kbjs_ArgumentTypeError),
                  FUNC_NAME,
                  "kb.rpi2.Event",
                  0,
                  duk_safe_to_string(context, (duk_idx_t)-5));

    /* STACK: [.., arg1, arg2] */
    duk_pop_3(context);

    /* If second argument is not an object */
    if (!duk_is_object(context, (duk_idx_t)-1))
        duk_error(context,
                  (duk_errcode_t)kbjs_ArgumentTypeError,
                  kbjs_Error_fmt(kbjs_ArgumentTypeError),
                  FUNC_NAME,
                  "kb.rpi2.PINn",
                  1,
                  duk_safe_to_string(context, (duk_idx_t)-1));

    /* STACK: [.., arg1, arg2, stash] */
    duk_push_heap_stash(context);
    /* STACK: [.., arg1, arg2, stash, {} */
    duk_get_prop_string(context, (duk_idx_t)-1, kbjs_PIN_ID_PROTO_STASH_KEY);
    /* STACK: [.., arg1, arg2, stash, {}, "INDEX"] */
    duk_get_prop_string(context, (duk_idx_t)-3, kbjs_PIN_ID_VALUE_KEY);
    /* STACK: [.., arg1, arg2, stash, {}, enum] */
    duk_get_prop(context, (duk_idx_t)-2);

    /* If second argument is not a PinId enum */
    if (!duk_strict_equals(context, (duk_idx_t)-1, (duk_idx_t)-4))
        duk_error(context,
                  (duk_errcode_t)kbjs_ArgumentTypeError,
                  kbjs_Error_fmt(kbjs_ArgumentTypeError),
                  FUNC_NAME,
                  "kb.rpi2.PINn",
                  1,
                  duk_safe_to_string(context, (duk_idx_t)-4));

    /* STACK: [.., arg1, arg2] */
    duk_pop_3(context);

    /* STACK: [.., arg1, arg2, void*] */
    duk_get_prop_string(context, (duk_idx_t)-2, KBJS_INSTANCE_PTR);
    /* STACK: [.., arg1, arg2, void*, void*] */
    duk_get_prop_string(context, (duk_idx_t)-2, KBJS_INSTANCE_PTR);

    kbjs_Event *kb_event  = duk_get_pointer(context, (duk_idx_t)-2);
    kbjs_PinId *kb_pin_id = duk_get_pointer(context, (duk_idx_t)-1);

    /* Create new LED instance */
    kbjs_LED *kb_led;
    if (!(kb_led = malloc(sizeof(kbjs_LED))))
        duk_error(context,
                  (duk_errcode_t)kbjs_AllocationError,
                  kbjs_Error_fmt(kbjs_AllocationError),
                  FUNC_NAME);

    /* Initialze instance as kibu LED */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_sensors_LED_ini((kb_rpi2_sensors_LED *const)kb_led,
                                            (kb_rpi2_Event *const)kb_event,
                                            kb_pin_id->id)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);

    /* STACK: [.., arg1, arg2] */
    duk_pop_2(context);

    /* Store javascript references */
    kb_led->js_context = context;
    kbjs_get_stash_key(KBJS_TYPES_STASH_KEY_LENGTH, kb_led->js_stash_key);

    /* STACK: [.., arg1, arg2] */
    duk_push_this(context);

    /* Set virtual methods */
    #define SET_VIRTUAL_METHODS(C_NAME, JS_NAME)                               \
        /* STACK: [args..., this, "NAME"] */                                   \
        duk_push_string(context, JS_NAME);                                     \
                                                                               \
        /* Create getter */                                                    \
        /* STACK: [args..., this, "NAME", getter] */                           \
        duk_push_c_function(context, C_NAME##_getter, (duk_idx_t)0);           \
        /* STACK: [args..., this, "NAME", getter, "getter"] */                 \
        duk_push_string(context, JS_NAME "_getter");                           \
        /* STACK: [args..., this, "NAME", getter] */                           \
        duk_put_prop_string(context, (duk_idx_t)-2, "name");                   \
                                                                               \
        /* Create setter */                                                    \
        /* STACK: [args..., this, "NAME", getter, setter] */                   \
        duk_push_c_function(context, C_NAME##_setter, (duk_idx_t)1);           \
        /* STACK: [args..., this, "NAME", getter, setter, "setter"] */         \
        duk_push_string(context, JS_NAME "_setter");                           \
        /* STACK: [args..., this, "NAME", getter, setter] */                   \
        duk_put_prop_string(context, (duk_idx_t)-2, "name");                   \
                                                                               \
        /* Store methods */                                                    \
        /* STACK: [args..., this] */                                           \
        duk_def_prop(context,                                                  \
                     (duk_idx_t)-4,                                            \
                     DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);
    SET_VIRTUAL_METHODS(on_enable,  "onEnable")
    SET_VIRTUAL_METHODS(on_disable, "onDisable")
    #undef SET_VIRTUAL_METHODS

    /* Create and store instance pointer */
    /* STACK: [..., arg1, arg2, this, ""] */
    duk_push_string(context, KBJS_INSTANCE_PTR);
    /* STACK: [..., arg1, arg2, this, "", void*] */
    duk_push_pointer(context, kb_led);
    /* STACK: [..., arg1, arg2, this] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create instance destructor */
    /* STACK: [..., arg1, arg2, this, LED_del] */
    duk_push_c_function(context, kbjs_LED_del, (duk_idx_t)1);
    /* STACK: [..., arg1, arg2, this] */
    duk_set_finalizer(context, (duk_idx_t)-2);

    /* Store `this` on stash */
    /* STACK: [..., arg1, arg2, this, stash] */
    duk_push_heap_stash(context);
    /* STACK: [..., arg1, arg2, this, stash, void*] */
    duk_push_string(context, kb_led->js_stash_key);
    /* STACK: [..., arg1, arg2, this, stash, void*, this] */
    duk_dup(context, (duk_idx_t)-3);
    /* STACK: [..., arg1, arg2, this, stash] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* STACK: [..., arg1, arg2, this] */
    duk_pop(context);

    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_LED_del(duk_context *context)
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
    static const char *FUNC_NAME = "kb.rpi2.sensors.LED.off()";

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
    duk_push_c_function(context, kbjs_LED_new, (duk_idx_t)2);

    /* Create kb.rpi2.Context.toString */
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "toString"] */
    duk_push_string(context, "toString");
    /* STACK: [global, kb, rpi, sensors, "LED", LED_new(), "toString", toString()] */
    duk_push_c_function(context, kbjs_LED_type_str, (duk_idx_t)0);
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
