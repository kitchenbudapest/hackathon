/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_context
            duk_ret_t
            duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    func  : kb_Error_str */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event
            kb_rpi2_Event_new
            kb_rpi2_Event_del */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/keys.h"
/*  macro : KBJS_NATIVE_OBJ
            KBJS_NATIVE_FUNC
            KBJS_INSTANCE_PTR */
#include "include/errors.h"
/*  const : kbjs_InternalError
            kbjs_InvocationError
            kbjs_ArgumentError
            kbjs_ArgumentTypeError
    func  : kbjs_Error_fmt */
#include "include/types.h"
/*  type  : kbjs_Context
            kbjs_Event */
#include "include/js_types.h"
/*  func  : kbjs_js_types_str */


/*----------------------------------------------------------------------------*/
/* Forward declarations */
static duk_ret_t
kbjs_Event_new(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_del(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_type_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_instance_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_activate(duk_context *context);



/*----------------------------------------------------------------------------*/
static duk_ret_t
kbjs_Event_new(duk_context *context)
{
    static const char *const FUNC_NAME = "kb.rpi2.Event() (initialize)";

    /* If function not called as a constructor */
    if (!duk_is_constructor_call(context))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InvocationError,
                  kbjs_Error_fmt(kbjs_InvocationError),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Check the type of the first argument */
    /* STACK: [args...,] */
    duk_idx_t type;
    switch ((type = duk_get_type(context, (duk_idx_t)0)))
    {
        case DUK_TYPE_OBJECT:
            break;

        default:
            duk_error(context,
                      (duk_errcode_t)kbjs_ArgumentTypeError,
                      kbjs_Error_fmt(kbjs_ArgumentTypeError),
                      FUNC_NAME,
                      kbjs_js_types_str(DUK_TYPE_OBJECT),
                      0,
                      kbjs_js_types_str(type));
            return (duk_ret_t)0;
    }

    // <<<<<<<<< TODO: if first argument does not have instance_ptr property !!!

    /* STACK: [args..., void*] */
    duk_get_prop_string(context, (duk_idx_t)0, KBJS_INSTANCE_PTR);
    /* STACK: [args..., void*] */
    kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

    /* Create new Event instance */
    kbjs_Event *kb_event;
    if (!(kb_event = malloc(sizeof(kbjs_Event))))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_AllocationError,
                  kbjs_Error_fmt(kbjs_AllocationError),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Initialize instance as kibu Event */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Event_ini((kb_rpi2_Event   *const)kb_event,
                                      (kb_rpi2_Context *const)kb_context)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* STACK: [args...] */
    duk_pop(context);

    // duk_error(context,
    //           (duk_errcode_t)kbjs_ArgumentError,
    //           kbjs_Error_fmt(kbjs_ArgumentError),
    //           FUNC_NAME,
    //           1,
    //           0);

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* Create and store instance pointer */
    /* STACK: [args..., this, ""] */
    duk_push_string(context, KBJS_INSTANCE_PTR);
    /* STACK: [args..., this, "", void*] */
    duk_push_pointer(context, kb_event);
    /* STACK: [args..., this] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create instance destructor */
    /* STACK: [args..., this, Event_del] */
    duk_push_c_function(context, kbjs_Event_del, (duk_idx_t)1);
    /* STACK: [args..., this] */
    duk_set_finalizer(context, (duk_idx_t)-2);

    /* Store `this` on stash */
    /* STACK: [args..., this, stash] */
    duk_push_heap_stash(context);
    /* STACK: [args..., this, stash, void*] */
    duk_push_pointer(context, kb_context);
    /* STACK: [args..., this, stash, void*, this] */
    duk_dup(context, (duk_idx_t)-3);
    /* STACK: [args..., this, stash] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* STACK: [args..., this] */
    duk_pop(context);

    /* Store javascript references */
    kb_event->js_context = context;

    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_del(duk_context *context)
{
    static const char *const FUNC_NAME = "kb.rpi2.Event() (finalize)";

    /* STACK: [this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_Event *kb_event = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Event instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Event_fin((kb_rpi2_Event *const)kb_event)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Deallocate instance */
    free(kb_event);

    /* STACK: [] */
    duk_pop_n(context, (duk_idx_t)2);
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_type_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_FUNC("kb.rpi2.Event"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_instance_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_OBJ("kb.rpi2.Event"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Event_activate(duk_context *context)
{
    static const char *const FUNC_NAME = "kb.rpi2.Event.activate()";

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* STACK: [this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_Event *kb_event = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Event instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Event_activate((kb_rpi2_Event *const)kb_event)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* STACK: [] */
    duk_pop_n(context, 2);
    return (duk_ret_t)0;
}


/*----------------------------------------------------------------------------*/
static const duk_function_list_entry kbjs_Event_methods[] =
{
    {"toString", kbjs_Event_instance_str, (duk_idx_t)0},
    {"activate", kbjs_Event_activate    , (duk_idx_t)0},
    {NULL      , NULL                   , (duk_idx_t)0},
};


/*----------------------------------------------------------------------------*/
void
kbjs_register_Event(duk_context *context)
{
    /* Get kb.rpi2 object */
    /* STACK: [global] */
    duk_push_global_object(context);
    /* STACK: [global, kb] */
    duk_get_prop_string(context, (duk_idx_t)-1, "kb");
    /* STACK: [global, kb, rpi] */
    duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");

    /* Create kb.rpi2.Event constructor */
    /* STACK: [global, kb, rpi, "Event"] */
    duk_push_string(context, "Event");
    /* STACK: [global, kb, rpi, "Event", Event_new()] */
    duk_push_c_function(context, kbjs_Event_new, (duk_idx_t)1);

    /* Create kb.rpi2.Event.toString */
    /* STACK: [global, kb, rpi, "Event", Event_new(), "toString"] */
    duk_push_string(context, "toString");
    /* STACK: [global, kb, rpi, "Event", Event_new(), "toString", toString()] */
    duk_push_c_function(context, kbjs_Event_type_str, (duk_idx_t)1);
    /* STACK: [global, kb, rpi, "Event", Event_new()] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create kb.rpi2.Event.prototype */
    /* STACK: [global, kb, rpi, "Event", Event_new(), "prototype"] */
    duk_push_string(context, "prototype");
    /* STACK: [global, kb, rpi, "Event", Event_new(), "prototype", {}] */
    duk_push_object(context);
    /* STACK: [global, kb, rpi, "Event", Event_new(), "prototype", {f...}] */
    duk_put_function_list(context, (duk_idx_t)-1, kbjs_Event_methods);

    /* Set prototype */
    /* STACK: [global, kb, rpi, "Event", Event_new()] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* Set constructor */
    /* STACK: [global, kb, rpi] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Clean up */
    /* STACK: [] */
    duk_pop_n(context, (duk_idx_t)3);
}
