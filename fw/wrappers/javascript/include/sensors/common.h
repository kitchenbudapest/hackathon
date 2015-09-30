/* INFO **
** INFO */

/* Header guard */
#ifndef KBJS_SENSORS_COMMON_H_1331567805515832
#define KBJS_SENSORS_COMMON_H_1331567805515832 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include jemalloc headers */
#include <jemalloc/jemalloc.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/**/

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_FAIL
    func  : kb_Error_str */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    func  : kb_rpi2_Sensor_bind_*
            kb_rpi2_Sensor_unbind_* */

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
#include "include/types.h"
/*  macro : KBJS_TYPES_STASH_KEY_LENGTH
    type  : kbjs_Context
            kbjs_Event
    func  : kbjs_get_stash_key */
#include "include/pin_ids.h"
/*  const : kbjs_PIN_ID_PROTO_STASH_KEY */
#include "include/js_types.h"
/*  func  : kbjs_js_types_str */


/*----------------------------------------------------------------------------*/
/* Create static functions:
    * C_NAME()
    * C_NAME_setter()
    * C_NAME_getter() */
#define KBJS_SENSORS_COMMON_CALLBACK_WRAPPER_SETTER_GETTER_(C_BASE,            \
                                                            C_NAME,            \
                                                            C_FUNC,            \
                                                            JS_NAME,           \
                                                            JS_FUNC)           \
    static kb_Error                                                            \
    C_FUNC(C_BASE          *const kb_sensor,                                   \
           kb_rpi2_Event   *const kb_event,                                    \
           kb_rpi2_Context *const kb_context)                                  \
    {                                                                          \
        /* STACK: [...] */                                                     \
        duk_context *context = ((kbjs_##C_NAME *const)kb_sensor)->js_context;  \
                                                                               \
        /* STACK: [..., stash] */                                              \
        duk_push_heap_stash(context);                                          \
                                                                               \
        /* STACK: [..., stash, ""] */                                          \
        duk_push_string(context,                                               \
                        ((kbjs_##C_NAME *const)kb_sensor)->js_stash_key);      \
        /* STACK: [..., stash, this] */                                        \
        duk_get_prop(context, (duk_idx_t)-2);                                  \
                                                                               \
        /* Get callback function-key*/                                         \
        /* STACK: [..., stash, this, "_JS_FUNC"] */                            \
        duk_push_string(context, "_" JS_FUNC);                                 \
        /* Set first argument */                                               \
        /* STACK: [..., stash, this, "_JS_FUNC", this] */                      \
        duk_dup(context, (duk_idx_t)-2);                                       \
                                                                               \
        /* Get/set second argument */                                          \
        /* STACK: [..., stash, this, "_JS_FUNC", this, event] */               \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-4,                                     \
                            ((kbjs_Event *const)kb_event)->js_stash_key);      \
                                                                               \
        /* Get/set third argument */                                           \
        /* STACK: [..., stash, this, "_JS_FUNC", this, event, context] */      \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-5,                                     \
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
    }                                                                          \
                                                                               \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static duk_ret_t                                                           \
    C_FUNC##_setter(duk_context *context)                                      \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2.sensors."                \
                                             JS_NAME "." JS_FUNC "_setter";    \
        kb_Error kb_error;                                                     \
        kbjs_##C_NAME *kb_sensor;                                              \
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
            kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);               \
                                                                               \
            /* Unset callback */                                               \
            if ((kb_error = C_BASE##_unbind_##C_FUNC(                          \
                    (C_BASE *const)kb_sensor)))                                \
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
            kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);               \
                                                                               \
            /* Unset callback */                                               \
            if ((kb_error = C_BASE##_bind_##C_FUNC(                            \
                    (C_BASE *const)kb_sensor,                                  \
                    C_FUNC)))                                                  \
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
        duk_put_prop_string(context, (duk_idx_t)-2, "_" JS_FUNC);              \
        /* STACK: [...] */                                                     \
        duk_pop(context);                                                      \
        return (duk_ret_t)0;                                                   \
    }                                                                          \
                                                                               \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static duk_ret_t                                                           \
    C_FUNC##_getter(duk_context *context)                                      \
    {                                                                          \
        /* STACK: [..., this] */                                               \
        duk_push_this(context);                                                \
        /* STACK: [..., this, value] */                                        \
        duk_get_prop_string(context, (duk_idx_t)-1, "_" JS_FUNC);              \
        return (duk_ret_t)1;                                                   \
    }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_SENSORS_COMMON_GENERIC_CALLBACK_WRAPPER_SETTER_GETTER(...)        \
    KBJS_SENSORS_COMMON_CALLBACK_WRAPPER_SETTER_GETTER_(kb_rpi2_Sensor,        \
                                                        __VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_SENSORS_COMMON_SPECIFIC_CALLBACK_WRAPPER_SETTER_GETTER(           \
    C_NAME,                                                                    \
    ...)                                                                       \
        KBJS_SENSORS_COMMON_CALLBACK_WRAPPER_SETTER_GETTER_(                   \
            kb_rpi2_sensors_##C_NAME,                                          \
            C_NAME,                                                            \
            __VA_ARGS__)                                                       \


/*----------------------------------------------------------------------------*/
/* Create static function: kbjs_C_NAME_C_METH() */
#define KBJS_SENSORS_COMMON_SIMPLE_METHODS_WRAPPER(C_NAME,                     \
                                                   C_METH,                     \
                                                   JS_NAME,                    \
                                                   JS_METH)                    \
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_##C_METH(duk_context *context)                             \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2.sensors."                \
                                             JS_NAME "." JS_METH "()";         \
                                                                               \
        /* STACK: [args..., this] */                                           \
        duk_push_this(context);                                                \
                                                                               \
        /* STACK: [args..., this, void*] */                                    \
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);        \
        kbjs_##C_NAME *kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);    \
                                                                               \
        /* Delete kibu Context instance */                                     \
        kb_Error kb_error;                                                     \
        if ((kb_error = kb_rpi2_sensors_##C_NAME##_##C_METH(                   \
                (kb_rpi2_sensors_##C_NAME *const)kb_sensor)))                  \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);                                              \
                                                                               \
        /* STACK: [args...] */                                                 \
        duk_pop_2(context);                                                    \
        return (duk_ret_t)0;                                                   \
    }


/*----------------------------------------------------------------------------*/
/* Create static function: <Number> kbjs_C_NAME_C_METH() */
#define KBJS_SENSORS_COMMON_NUMBER_RETURNED_SIMPLE_METHODS_WRAPPER(C_NAME,     \
                                                                   C_METH,     \
                                                                   JS_NAME,    \
                                                                   JS_METH)    \
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_##C_METH(duk_context *context)                             \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2.sensors."                \
                                             JS_NAME "." JS_METH "()";         \
                                                                               \
        /* STACK: [..., this] */                                               \
        duk_push_this(context);                                                \
                                                                               \
        /* STACK: [..., this, void*] */                                        \
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);        \
        kbjs_##C_NAME *kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);    \
                                                                               \
        /* Delete kibu Context instance */                                     \
        double value;                                                          \
        kb_Error kb_error;                                                     \
        if ((kb_error = kb_rpi2_sensors_##C_NAME##_##C_METH(                   \
                (kb_rpi2_sensors_##C_NAME *const)kb_sensor, &value)))          \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);                                              \
                                                                               \
        /* STACK: [...] */                                                     \
        duk_pop_2(context);                                                    \
        /* STACK: [..., bool] */                                               \
        duk_push_number(context, (duk_double_t)value);                         \
        return (duk_ret_t)1;                                                   \
    }


/*----------------------------------------------------------------------------*/
/* Create static function: kbjs_C_NAME_C_METH(<double>) */
#define KBJS_SENSORS_COMMON_SINGLE_NUMBER_METHODS_WRAPPER(C_NAME,              \
                                                          C_METH,              \
                                                          JS_NAME,             \
                                                          JS_METH)             \
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_##C_METH(duk_context *context)                             \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2.sensors."                \
                                             JS_NAME "." JS_METH "()";         \
                                                                               \
        /* If the given argument is not a number */                            \
        /* STACK: [..., arg] */                                                \
        if (!duk_is_number(context, (duk_idx_t)-1))                            \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_ArgumentTypeError,                   \
                      kbjs_Error_fmt(kbjs_ArgumentTypeError),                  \
                      FUNC_NAME,                                               \
                      "Number",                                                \
                      0,                                                       \
                      duk_safe_to_string(context,                              \
                                         (duk_idx_t)-1));                      \
        /* Store the value */                                                  \
        double value = (double)duk_get_number(context, (duk_idx_t)-1);         \
                                                                               \
        /* STACK: [..., arg, this] */                                          \
        duk_push_this(context);                                                \
                                                                               \
        /* STACK: [..., arg, this, void*] */                                   \
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);        \
        kbjs_##C_NAME *kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);    \
                                                                               \
        /* Delete kibu Context instance */                                     \
        kb_Error kb_error;                                                     \
        if ((kb_error = kb_rpi2_sensors_##C_NAME##_##C_METH(                   \
                (kb_rpi2_sensors_##C_NAME *const)kb_sensor, value)))           \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);                                              \
                                                                               \
        /* STACK: [..., arg] */                                                \
        duk_pop_2(context);                                                    \
        return (duk_ret_t)0;                                                   \
    }


/*----------------------------------------------------------------------------*/
/* Has to be the 5th+ argument of NEW_DELETE_TO_STRING macro */
#define KBJS_SENSORS_COMMON_PINS_ARGUMENTS(INDEX)                              \
    ((kbjs_PinId *const)duk_get_pointer(                                       \
        context,                                                               \
        (duk_idx_t)INDEX))->id

/*----------------------------------------------------------------------------*/
/* Has to be the 3rd argument of NEW_DELETE_TO_STRING macro */
#define KBJS_SENSORS_COMMON_SET_VIRTUAL_METHODS(C_FUNC, JS_FUNC)               \
        /* STACK: [args..., this, "NAME"] */                                   \
        duk_push_string(context, JS_FUNC);                                     \
                                                                               \
        /* Create getter */                                                    \
        /* STACK: [args..., this, "NAME", getter] */                           \
        duk_push_c_function(context, C_FUNC##_getter, (duk_idx_t)0);           \
        /* STACK: [args..., this, "NAME", getter, "getter"] */                 \
        duk_push_string(context, JS_FUNC "_getter");                           \
        /* STACK: [args..., this, "NAME", getter] */                           \
        duk_put_prop_string(context, (duk_idx_t)-2, "name");                   \
                                                                               \
        /* Create setter */                                                    \
        /* STACK: [args..., this, "NAME", getter, setter] */                   \
        duk_push_c_function(context, C_FUNC##_setter, (duk_idx_t)1);           \
        /* STACK: [args..., this, "NAME", getter, setter, "setter"] */         \
        duk_push_string(context, JS_FUNC "_setter");                           \
        /* STACK: [args..., this, "NAME", getter, setter] */                   \
        duk_put_prop_string(context, (duk_idx_t)-2, "name");                   \
                                                                               \
        /* Store methods */                                                    \
        /* STACK: [args..., this] */                                           \
        duk_def_prop(context,                                                  \
                     (duk_idx_t)-4,                                            \
                     DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);


/*----------------------------------------------------------------------------*/
/* Create static functions:
    * kbjs_C_NAME_del
    * kbjs_C_NAME_new
    * kbjs_C_NAME_type_str
    * kbjs_C_NAME_instance_str */
#define KBJS_SENSORS_COMMON_NEW_DELETE_TO_STRING_WRAPPER(C_NAME,               \
                                                         JS_NAME,              \
                                                         VIRTUAL_METHODS,      \
                                                         PINS_ARG_COUNT,       \
                                                         ...)                  \
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_del(duk_context *context)                                  \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2." JS_NAME "_finalize()"; \
                                                                               \
        /* STACK: [this, void*] */                                             \
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);        \
        kbjs_##C_NAME *kb_sensor = duk_get_pointer(context, (duk_idx_t)-1);    \
                                                                               \
        /* Delete kibu Context instance */                                     \
        kb_Error kb_error;                                                     \
        if ((kb_error = kb_rpi2_sensors_##C_NAME##_fin(                        \
                (kb_rpi2_sensors_##C_NAME *const)kb_sensor)))                  \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);                                              \
                                                                               \
        /* Deallocate instance */                                              \
        free(kb_sensor);                                                       \
                                                                               \
        /* STACK: [] */                                                        \
        duk_pop_2(context);                                                    \
        return (duk_ret_t)0;                                                   \
    }                                                                          \
                                                                               \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_new(duk_context *context)                                  \
    {                                                                          \
        static const char *const FUNC_NAME = "kb.rpi2.sensors."                \
                                             JS_NAME "_initialize()";          \
                                                                               \
        /* If function not called as a constructor */                          \
        if (!duk_is_constructor_call(context))                                 \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InvocationError,                     \
                      kbjs_Error_fmt(kbjs_InvocationError),                    \
                      FUNC_NAME);                                              \
                                                                               \
        /* STACK: [..., arg1, arg2, kb] */                                     \
        duk_get_global_string(context, "kb");                                  \
        /* STACK: [..., arg1, arg2, kb, rpi2] */                               \
        duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");                   \
        /* STACK: [..., arg1, arg2, kb, rpi2, Event] */                        \
        duk_get_prop_string(context, (duk_idx_t)-1, "Event");                  \
                                                                               \
        /* If first argument is not an instance of kb.rpi2.Event */            \
        if (!duk_instanceof(context,                                           \
                            (duk_idx_t)-(PINS_ARG_COUNT + 4),                  \
                            (duk_idx_t)-1))                                    \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_ArgumentTypeError,                   \
                      kbjs_Error_fmt(kbjs_ArgumentTypeError),                  \
                      FUNC_NAME,                                               \
                      "kb.rpi2.Event",                                         \
                      0,                                                       \
                      duk_safe_to_string(context,                              \
                                         (duk_idx_t)-(PINS_ARG_COUNT + 4)));   \
                                                                               \
        /* STACK: [.., arg1, ..., argn] */                                     \
        duk_pop_3(context);                                                    \
                                                                               \
        /* STACK: [.., arg1, ..., argn, void*] */                              \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-(PINS_ARG_COUNT + 1),                  \
                            KBJS_INSTANCE_PTR);                                \
        kbjs_Event *kb_event = duk_get_pointer(context, (duk_idx_t)-1);        \
                                                                               \
        /* STACK: [.., arg1, ..., argn] */                                     \
        duk_pop(context);                                                      \
                                                                               \
        /* Get enum prototype look-up object */                                \
        /* STACK: [.., arg1, ..., argn, stash] */                              \
        duk_push_heap_stash(context);                                          \
        /* STACK: [.., arg1, ..., argn, stash, {} */                           \
        duk_get_prop_string(context,                                           \
                            (duk_idx_t)-1,                                     \
                            kbjs_PIN_ID_PROTO_STASH_KEY);                      \
        /* STACK: [.., arg1, ..., argn, {}, stash */                           \
        duk_swap_top(context, (duk_idx_t)-2);                                  \
        /* STACK: [.., arg1, ..., argn, {} */                                  \
        duk_pop(context);                                                      \
                                                                               \
        /* Get pointers to PinId enums from arguments */                       \
        duk_idx_t offset = (duk_idx_t)-(PINS_ARG_COUNT + 1);                   \
        for (duk_idx_t i=1; i<(PINS_ARG_COUNT + (duk_idx_t)1); i++)            \
        {                                                                      \
            /* If nth argument is not an object */                             \
            if (!duk_is_object(context, offset))                               \
                duk_error(context,                                             \
                          (duk_errcode_t)kbjs_ArgumentTypeError,               \
                          kbjs_Error_fmt(kbjs_ArgumentTypeError),              \
                          FUNC_NAME,                                           \
                          "kb.rpi2.PINx",                                      \
                          i,                                                   \
                          duk_safe_to_string(context, offset));                \
                                                                               \
            /* STACK: [.., arg1, ..., argn, {}, "INDEX"] */                    \
            duk_get_prop_string(context, offset, kbjs_PIN_ID_VALUE_KEY);       \
            /* STACK: [.., arg1, ..., argn, {}, enum] */                       \
            duk_get_prop(context, (duk_idx_t)-2);                              \
                                                                               \
            /* If nth argument is not a PinId enum */                          \
            if (!duk_strict_equals(context,                                    \
                                   (duk_idx_t)-1,                              \
                                   offset - (duk_idx_t)1))                     \
                duk_error(context,                                             \
                          (duk_errcode_t)kbjs_ArgumentTypeError,               \
                          kbjs_Error_fmt(kbjs_ArgumentTypeError),              \
                          FUNC_NAME,                                           \
                          "kb.rpi2.PINx",                                      \
                          i,                                                   \
                          duk_safe_to_string(context, offset - (duk_idx_t)1)); \
                                                                               \
            /* STACK: [.., arg1, ..., argn, {}] */                             \
            duk_pop(context);                                                  \
            /* STACK: [.., arg1, ..., argn, {}, void*] */                      \
            duk_get_prop_string(context, offset, KBJS_INSTANCE_PTR);           \
            /* STACK: [.., arg1, ..., argn, void*, {}] */                      \
            duk_swap_top(context, (duk_idx_t)-2);                              \
        }                                                                      \
        /* STACK: [.., arg1, ..., argn, void1*, ..., voidn*] */                \
        duk_pop(context);                                                      \
                                                                               \
        /* Create new C_NAME instance */                                       \
        kbjs_##C_NAME *kb_sensor;                                              \
        if (!(kb_sensor = malloc(sizeof(kbjs_##C_NAME))))                      \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_AllocationError,                     \
                      kbjs_Error_fmt(kbjs_AllocationError),                    \
                      FUNC_NAME);                                              \
                                                                               \
        /* Initialze instance as kibu C_NAME */                                \
        kb_Error kb_error;                                                     \
        if ((kb_error = kb_rpi2_sensors_##C_NAME##_ini(                        \
                (kb_rpi2_sensors_##C_NAME *const)kb_sensor,                    \
                (kb_rpi2_Event *const)kb_event,                                \
                __VA_ARGS__)))                                                 \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);                                              \
                                                                               \
        /* STACK: [.., arg1, ..., argn] */                                     \
        duk_pop_n(context, (duk_idx_t)PINS_ARG_COUNT);                         \
                                                                               \
        /* Store javascript references */                                      \
        kb_sensor->js_context = context;                                       \
        kbjs_get_stash_key(KBJS_TYPES_STASH_KEY_LENGTH,                        \
                           kb_sensor->js_stash_key);                           \
                                                                               \
        /* STACK: [..., arg1, ..., argn, this */                               \
        duk_push_this(context);                                                \
                                                                               \
        /* Set virtual methods */                                              \
        VIRTUAL_METHODS                                                        \
                                                                               \
        /* Create and store instance pointer */                                \
        /* STACK: [..., arg1, ..., argn, this, ""] */                          \
        duk_push_string(context, KBJS_INSTANCE_PTR);                           \
        /* STACK: [..., arg1, ..., argn, this, "", void*] */                   \
        duk_push_pointer(context, kb_sensor);                                  \
        /* STACK: [..., arg1, ..., argn, this] */                              \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* Create instance destructor */                                       \
        /* STACK: [..., arg1, ..., argn, this, C_NAME_del] */                  \
        duk_push_c_function(context, kbjs_##C_NAME##_del, (duk_idx_t)1);       \
        /* STACK: [..., arg1, ..., argn, this] */                              \
        duk_set_finalizer(context, (duk_idx_t)-2);                             \
                                                                               \
        /* Store `this` on stash */                                            \
        /* STACK: [..., arg1, ..., argn, this, stash] */                       \
        duk_push_heap_stash(context);                                          \
        /* STACK: [..., arg1, ..., argn, this, stash, void*] */                \
        duk_push_string(context, kb_sensor->js_stash_key);                     \
        /* STACK: [..., arg1, ..., argn, this, stash, void*, this] */          \
        duk_dup(context, (duk_idx_t)-3);                                       \
        /* STACK: [..., arg1, ..., argn, this, stash] */                       \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
        /* STACK: [..., arg1, ..., argn, this] */                              \
        duk_pop(context);                                                      \
                                                                               \
        return (duk_ret_t)0;                                                   \
    }                                                                          \
                                                                               \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_type_str(duk_context *context)                             \
    {                                                                          \
        duk_push_string(context, KBJS_NATIVE_FUNC("kb.rpi2.sensors." JS_NAME));\
        return (duk_ret_t)1;                                                   \
    }                                                                          \
                                                                               \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static duk_ret_t                                                           \
    kbjs_##C_NAME##_instance_str(duk_context *context)                         \
    {                                                                          \
        duk_push_string(context, KBJS_NATIVE_OBJ("kb.rpi2.sensors." JS_NAME)); \
        return (duk_ret_t)1;                                                   \
    }


/*----------------------------------------------------------------------------*/
#define KBJS_SENSORS_COMMON_REGISTER_WRAPPER_H(C_NAME)                         \
    void                                                                       \
    kbjs_register_##C_NAME(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_SENSORS_COMMON_REGISTER_WRAPPER_C(C_NAME, JS_NAME, ARG_COUNT)     \
    void                                                                       \
    kbjs_register_##C_NAME(duk_context *context)                               \
    {                                                                          \
        /* Get kb.rpi2.sensors object */                                       \
        /* STACK: [global] */                                                  \
        duk_push_global_object(context);                                       \
        /* STACK: [global, kb] */                                              \
        duk_get_prop_string(context, (duk_idx_t)-1, "kb");                     \
        /* STACK: [global, kb, rpi] */                                         \
        duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");                   \
        /* STACK: [global, kb, rpi, sensors, sensors] */                       \
        duk_get_prop_string(context, (duk_idx_t)-1, "sensors");                \
                                                                               \
        /* Create kb.rpi2.sensors.JS_NAME constructor */                       \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME"] */                     \
        duk_push_string(context, JS_NAME);                                     \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_push_c_function(context,                                           \
                            kbjs_##C_NAME##_new,                               \
                            (duk_idx_t)ARG_COUNT);                             \
                                                                               \
        /* Create kb.rpi2.Context.toString */                                  \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), ""] */            \
        duk_push_string(context, "toString");                                  \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", f()] */       \
        duk_push_c_function(context, kbjs_##C_NAME##_type_str, (duk_idx_t)0);  \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* Create kb.rpi2.Context.prototype */                                 \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), ""] */            \
        duk_push_string(context, "prototype");                                 \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", {}] */        \
        duk_push_object(context);                                              \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", {f...}] */    \
        duk_put_function_list(context, (duk_idx_t)-1, kbjs_##C_NAME##_methods);\
                                                                               \
        /* Set prototype */                                                    \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
        /* Set constructor */                                                  \
        /* STACK: [global, kb, rpi, sensors] */                                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* Clean up */                                                         \
        /* STACK: [] */                                                        \
        duk_pop_n(context, (duk_idx_t)4);                                      \
    }


#endif /* KBJS_SENSORS_COMMON_H_1331567805515832 */
