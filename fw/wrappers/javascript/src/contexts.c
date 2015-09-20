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
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  : kb_rpi2_Context_new
            kb_rpi2_Context_del */

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
            kbjs_PropertyTypeError
    func  : kbjs_Error_fmt */
#include "include/types.h"
/*  type  : kbjs_Context
            kbjs_Event */
#include "include/js_types.h"
/*  func  : kbjs_js_types_str */


/*----------------------------------------------------------------------------*/
/* Forward declarations */
static duk_ret_t
kbjs_Context_new(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_del(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_type_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_instance_str(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_start(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_stop(duk_context *context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_exit(duk_context *context);



/*----------------------------------------------------------------------------*/
/* Callback wrappers */
static kb_Error
on_cycle_end(kb_rpi2_Context *const kb_context,
             kb_rpi2_Event   *const kb_event)
{
    static const char *PROP_NAME = "kb.rpi2.Context.onCycleEnd";

    /* STACK: [...] */
    duk_context *context = ((kbjs_Context *const)kb_context)->js_context;

    /* STACK: [..., stash] */
    duk_push_heap_stash(context);
    /* STACK: [..., stash, void*] */
    duk_push_pointer(context, kb_context);
    /* STACK: [..., stash, this] */
    duk_get_prop(context, (duk_idx_t)-2);

    /* STACK: [..., stash, this, this.onCycleEnd] */
    duk_get_prop_string(context, (duk_idx_t)-1, "onCycleEnd");
    fputs("(oce) dump 0: ", stderr);
    duk_dump_context_stderr(context);

    /*
     * <<<<<<<<< type can be function or undefined
     */

    if (!duk_is_callable(context, (duk_idx_t)-1))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_PropertyTypeError,
                  kbjs_Error_fmt(kbjs_PropertyTypeError),
                  PROP_NAME,
                  kbjs_js_types_str(duk_get_type(context, (duk_idx_t)-1)));
        return kb_FAIL;
    }

    // /* STACK: [..., Context, Context.onCycleEnd, Context] */
    // duk_dup(context, (duk_idx_t)-2);
    // /* STACK: [..., Context, Context.onCycleEnd, Context, Event] */
    // duk_push_heapptr(context, ((kbjs_Event *const)kb_event)->js_object);
    // /* STACK: [..., Context, result] */
    // duk_call(context, (duk_idx_t)2);
    // /* STACK: [..., Context, result] */
    // kb_Error error = kb_OKAY;
    // /* STACK: [..., Context, bool] */
    // if (duk_to_boolean(context, (duk_idx_t)-1))
    //     error = kb_FAIL;
    //
    // /* STACK: [...] */
    // duk_pop_n(context, (duk_idx_t)2);
    // return error;

    (void)kb_event;
    return kb_OKAY;
}



/*----------------------------------------------------------------------------*/
/* Instance methods */
static duk_ret_t
kbjs_Context_new(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.Context() (initialize)";

    /* If function not called as a constructor */
    if (!duk_is_constructor_call(context))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InvocationError,
                  kbjs_Error_fmt(kbjs_InvocationError),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Create new Context instance */
    kbjs_Context *kb_context;
    if (!(kb_context = malloc(sizeof(kbjs_Context))))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_AllocationError,
                  kbjs_Error_fmt(kbjs_AllocationError),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Initialze instance as kibu Context */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_ini((kb_rpi2_Context *const)kb_context)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Set callback wrappers */
    if ((kb_error = kb_rpi2_Context_bind_on_cycle_end((kb_rpi2_Context *const)kb_context,
                                                      on_cycle_end)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* STACK: [args..., this] */
    duk_push_this(context);

    fputs("(new) dump 0: ", stderr);
    duk_dump_context_stderr(context);

    /* Create and store instance pointer */
    /* STACK: [args..., this, ""] */
    duk_push_string(context, KBJS_INSTANCE_PTR);
    /* STACK: [args..., this, "", void*] */
    duk_push_pointer(context, kb_context);

    fputs("(new) dump 1: ", stderr);
    duk_dump_context_stderr(context);

    /* STACK: [args..., this] */
    duk_put_prop(context, (duk_idx_t)-3);


    fputs("(new) dump 2: ", stderr);
    duk_dump_context_stderr(context);

    /* Create instance destructor */
    /* STACK: [args..., this, Context_del] */
    duk_push_c_function(context, kbjs_Context_del, (duk_idx_t)1);
    /* STACK: [args..., this] */
    duk_set_finalizer(context, (duk_idx_t)-2);

    /* Store `this` on stash */
    /* STACK: [args..., this, stash] */
    duk_push_heap_stash(context);
    /* STACK: [args..., this, stash, void*] */
    duk_push_pointer(context, kb_context);
    /* STACK: [args..., this, stash, void*, this] */
    duk_dup(context, (duk_idx_t)-3);

    fputs("(new) dump 3: ", stderr);
    duk_dump_context_stderr(context);

    /* STACK: [args..., this, stash] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* STACK: [args..., this] */
    duk_pop(context);

    /* Store javascript references */
    kb_context->js_context = context;

    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_del(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.Context() (finalize)";

    /* STACK: [this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_fin((kb_rpi2_Context *const)kb_context)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* Deallocate instance */
    free(kb_context);

    /* STACK: [] */
    duk_pop_n(context, (duk_idx_t)2);
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_type_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_FUNC("kb.rpi2.Context"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_instance_str(duk_context *context)
{
    duk_push_string(context, KBJS_NATIVE_OBJ("kb.rpi2.Context"));
    return (duk_ret_t)1;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_start(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.Context.start()";

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* STACK: [args..., this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_start((kb_rpi2_Context *const)kb_context)))
    {
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);
        return (duk_ret_t)0;
    }

    /* STACK: [args...] */
    duk_pop_n(context, 2);
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_stop(duk_context *context)
{
    (void)context;
    return (duk_ret_t)0;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static duk_ret_t
kbjs_Context_exit(duk_context *context)
{
    (void)context;
    return (duk_ret_t)0;
}


/*----------------------------------------------------------------------------*/
static const duk_function_list_entry kbjs_Context_methods[] =
{
    {"toString", kbjs_Context_instance_str, (duk_idx_t)0},
    {"start"   , kbjs_Context_start       , (duk_idx_t)0},
    {"stop"    , kbjs_Context_stop        , (duk_idx_t)0},
    {"exit"    , kbjs_Context_exit        , (duk_idx_t)0},
    {NULL      , NULL                     , (duk_idx_t)0},
};


/*----------------------------------------------------------------------------*/
void
kbjs_register_Context(duk_context *context)
{
    /* Get kb.rpi2 object */
    /* STACK: [global] */
    duk_push_global_object(context);
    /* STACK: [global, kb] */
    duk_get_prop_string(context, (duk_idx_t)-1, "kb");
    /* STACK: [global, kb, rpi] */
    duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");

    /* Create kb.rpi2.Context constructor */
    /* STACK: [global, kb, rpi, "Context"] */
    duk_push_string(context, "Context");
    /* STACK: [global, kb, rpi, "Context", Context_new()] */
    duk_push_c_function(context, kbjs_Context_new, (duk_idx_t)0);

    /* Create kb.rpi2.Context.toString */
    /* STACK: [global, kb, rpi, "Context", Context_new(), "toString"] */
    duk_push_string(context, "toString");
    /* STACK: [global, kb, rpi, "Context", Context_new(), "toString", toString()] */
    duk_push_c_function(context, kbjs_Context_type_str, (duk_idx_t)1);
    /* STACK: [global, kb, rpi, "Context", Context_new()] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create kb.rpi2.Context.prototype */
    /* STACK: [global, kb, rpi, "Context", Context_new(), "prototype"] */
    duk_push_string(context, "prototype");
    /* STACK: [global, kb, rpi, "Context", Context_new(), "prototype", {}] */
    duk_push_object(context);
    /* STACK: [global, kb, rpi, "Context", Context_new(), "prototype", {f...}] */
    duk_put_function_list(context, (duk_idx_t)-1, kbjs_Context_methods);

    /* Set prototype */
    /* STACK: [global, kb, rpi, "Context", Context_new()] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* Set constructor */
    /* STACK: [global, kb, rpi] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Clean up */
    /* STACK: [] */
    duk_pop_n(context, (duk_idx_t)3);
}
