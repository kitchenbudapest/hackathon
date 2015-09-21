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
/*  macro : KBJS_TYPES_STASH_KEY_LENGTH
    type  : kbjs_Context
            kbjs_Event
    func  : kbjs_get_stash_key */
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
#define CALLBACK_WRAPPERS(CNAME, JSNAME)                                       \
    static kb_Error                                                            \
    CNAME(kb_rpi2_Context *const kb_context,                                   \
          kb_rpi2_Event   *const kb_event)                                     \
    {                                                                          \
        static const char *PROP_NAME = "kb.rpi2.Context." JSNAME;              \
                                                                               \
        /* STACK: [...] */                                                     \
        duk_context *context = ((kbjs_Context *const)kb_context)->js_context;  \
                                                                               \
        /* STACK: [..., stash] */                                              \
        duk_push_heap_stash(context);                                          \
                                                                               \
        /* STACK: [..., stash, int] */                                         \
        duk_push_string(context,                                               \
                        ((kbjs_Context *const)kb_context)->js_stash_key);      \
        /* STACK: [..., stash, this] */                                        \
        duk_get_prop(context, (duk_idx_t)-2);                                  \
                                                                               \
        /* STACK: [..., stash, this, int] */                                   \
        duk_push_string(context, ((kbjs_Event *const)kb_event)->js_stash_key); \
        /* STACK: [..., stash, this, event] */                                 \
        duk_get_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* STACK: [..., stash, this, event, this.JSNAME] */                    \
        duk_get_prop_string(context, (duk_idx_t)-2, JSNAME);                   \
        /* If the given value is undefined */                                  \
        if (duk_is_undefined(context, (duk_idx_t)-1))                          \
            return kb_OKAY;                                                    \
        /* If the given value is not a function */                             \
        else if (!duk_is_callable(context, (duk_idx_t)-1))                     \
        {                                                                      \
            duk_error(context,                                                 \
                  (duk_errcode_t)kbjs_PropertyTypeError,                       \
                  kbjs_Error_fmt(kbjs_PropertyTypeError),                      \
                  PROP_NAME,                                                   \
                  kbjs_js_types_str(duk_get_type(context, (duk_idx_t)-1)));    \
            return kb_FAIL;                                                    \
        }                                                                      \
                                                                               \
        /* STACK: [..., stash, this, event, this.JSNAME, this] */              \
        duk_dup(context, (duk_idx_t)-3);                                       \
        /* STACK: [..., stash, this, event, this.JSNAME, this, event] */       \
        duk_dup(context, (duk_idx_t)-3);                                       \
        /* STACK: [..., stash, this, event, result] */                         \
        duk_call(context, (duk_idx_t)2);                                       \
                                                                               \
        kb_Error error = kb_OKAY;                                              \
        if (duk_to_boolean(context, (duk_idx_t)-1))                            \
            error = kb_FAIL;                                                   \
                                                                               \
        /* STACK: [...] */                                                     \
        duk_pop_n(context, (duk_idx_t)4);                                      \
        return error;                                                          \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create callback wrappers */
CALLBACK_WRAPPERS(on_start,       "onStart")
CALLBACK_WRAPPERS(on_cycle_begin, "onCycleBegin")
CALLBACK_WRAPPERS(on_cycle_end,   "onCycleEnd")
CALLBACK_WRAPPERS(on_stop,        "onStop")
CALLBACK_WRAPPERS(on_exit,        "onExit")
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static kb_Error
on_activate(kb_rpi2_Context *const kb_context,
            kb_rpi2_Event   *const kb_curr_event,
            kb_rpi2_Event   *const kb_next_event)
{
    /* STACK: [...] */
    duk_context *context = ((kbjs_Context *const)kb_context)->js_context;

    /* STACK: [..., stash] */
    duk_push_heap_stash(context);

    /* STACK: [..., stash, ""] */
    duk_push_string(context, ((kbjs_Context *const)kb_context)->js_stash_key);
    /* STACK: [..., stash, this] */
    duk_get_prop(context, (duk_idx_t)-2);

    /* STACK: [..., stash, this, "onActivate"] */
    duk_push_string(context, "onActivate");
    /* STACK: [..., stash, this, "onActivate", this] */
    duk_dup(context, (duk_idx_t)-2);

    /* If nth activation call */
    if (kb_curr_event)
    {
        /* Get curr_event */
        /* STACK: [..., stash, this, "onActivate", this, ""] */
        duk_push_string(context, ((kbjs_Event *const)kb_curr_event)->js_stash_key);
        /* STACK: [..., stash, this, "onActivate", this, curr] */
        duk_get_prop(context, (duk_idx_t)-5);
    }
    /* If first activation call */
    else
        /* STACK: [..., stash, this, "onActivate", this, curr=undefined] */
        duk_push_undefined(context);

    /* Get next_event */
    /* STACK: [..., stash, this, "onActivate", this, curr, ""] */
    duk_push_string(context, ((kbjs_Event *const)kb_next_event)->js_stash_key);
    /* STACK: [..., stash, this, "onActivate", this, curr, next] */
    duk_get_prop(context, (duk_idx_t)-6);

    /* Try to call callback */
    /* STACK: [..., stash, this, result] */
    duk_call_prop(context, (duk_idx_t)-5, (duk_idx_t)3);

    kb_Error error = kb_OKAY;
    /* STACK: [..., stash, this, bool(result)] */
    if (duk_to_boolean(context, (duk_idx_t)-1))
        error = kb_FAIL;

    /* STACK: [...] */
    duk_pop_3(context);
    return error;
}


/*----------------------------------------------------------------------------*/
static duk_ret_t
on_activate_setter(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.Context.onActivate (setter)";

    puts(FUNC_NAME);

    /* STACK: [..., arg] */
    /* If argument is undefined */
    if (duk_is_undefined(context, (duk_idx_t)-1))
    {
        /* If the given value is something else */
        /* STACK: [..., arg, this] */
        duk_push_this(context);

        /* STACK: [..., arg, this, ""] */
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
        /* STACK: [..., arg, this, void*] */
        kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

        /* Unset callback */
        kb_Error kb_error;
        if ((kb_error = kb_rpi2_Context_unbind_on_activate(
                (kb_rpi2_Context *const)kb_context)))
                    duk_error(context,
                              (duk_errcode_t)kbjs_InternalError,
                              kbjs_Error_fmt(kbjs_InternalError),
                              kb_Error_str(kb_error),
                              FUNC_NAME);

        /* Set value */
        /* STACK: [..., arg, this] */
        // duk_pop(context);
        /* STACK: [..., arg, this, undefined] */
        // duk_push_undefined(context);
    }
    /* If argument is a function */
    else if (duk_is_callable(context, (duk_idx_t)-1))
    {
        /* If the given value is something else */
        /* STACK: [..., arg, this] */
        duk_push_this(context);

        /* STACK: [..., arg, this, ""] */
        duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
        /* STACK: [..., arg, this, void*] */
        kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

        /* Unset callback */
        kb_Error kb_error;
        if ((kb_error = kb_rpi2_Context_bind_on_activate(
                (kb_rpi2_Context *const)kb_context,
                on_activate)))
                    duk_error(context,
                              (duk_errcode_t)kbjs_InternalError,
                              kbjs_Error_fmt(kbjs_InternalError),
                              kb_Error_str(kb_error),
                              FUNC_NAME);

        /* Set value */
        /* STACK: [..., arg, this] */
        // duk_pop(context);
        // /* STACK: [..., arg, this, function] */
        // duk_dup(context, (duk_idx_t)-2);
        // fputs("==> STACK: ", stderr);
        // duk_dump_context_stderr(context);
    }
    /* If argument is something else */
    else
        duk_error(context,
                  (duk_errcode_t)kbjs_PropertyTypeError,
                  kbjs_Error_fmt(kbjs_PropertyTypeError),
                  FUNC_NAME,
                  kbjs_js_types_str(duk_get_type(context, (duk_idx_t)-1)));

    fputs("==> STACK: ", stderr);
    duk_dump_context_stderr(context);

    /* STACK: [..., arg] */
    duk_pop_2(context);
    /* STACK: [..., arg, arg] */
    duk_dup(context, (duk_idx_t)-1);

    // /* STACK: [..., arg, this] */
    // // duk_put_prop_string(context, (duk_idx_t)-2, "onActivate");
    // /* STACK: [..., arg] */
    // duk_pop_2(context);

    fputs("==> STACK: ", stderr);
    duk_dump_context_stderr(context);

    return (duk_ret_t)1;
}


/*----------------------------------------------------------------------------*/
/* Instance methods */
static duk_ret_t
kbjs_Context_new(duk_context *context)
{
    static const char *FUNC_NAME = "kb.rpi2.Context() (initialize)";

    /* If function not called as a constructor */
    if (!duk_is_constructor_call(context))
        duk_error(context,
                  (duk_errcode_t)kbjs_InvocationError,
                  kbjs_Error_fmt(kbjs_InvocationError),
                  FUNC_NAME);

    /* Create new Context instance */
    kbjs_Context *kb_context;
    if (!(kb_context = malloc(sizeof(kbjs_Context))))
        duk_error(context,
                  (duk_errcode_t)kbjs_AllocationError,
                  kbjs_Error_fmt(kbjs_AllocationError),
                  FUNC_NAME);

    /* Initialze instance as kibu Context */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_ini((kb_rpi2_Context *const)kb_context)))
        duk_error(context,
                  (duk_errcode_t)kbjs_InternalError,
                  kbjs_Error_fmt(kbjs_InternalError),
                  kb_Error_str(kb_error),
                  FUNC_NAME);

    /* Set callback wrappers */
    #define BIND_FUNCTION(FNAME)                                               \
        if ((kb_error = kb_rpi2_Context_bind_##FNAME(                          \
                (kb_rpi2_Context *const)kb_context,                            \
                FNAME)))                                                       \
            duk_error(context,                                                 \
                      (duk_errcode_t)kbjs_InternalError,                       \
                      kbjs_Error_fmt(kbjs_InternalError),                      \
                      kb_Error_str(kb_error),                                  \
                      FUNC_NAME);
    BIND_FUNCTION(on_start)
    BIND_FUNCTION(on_cycle_begin)
    BIND_FUNCTION(on_cycle_end)
    BIND_FUNCTION(on_stop)
    BIND_FUNCTION(on_exit)

    /* Store javascript references */
    kb_context->js_context = context;
    kbjs_get_stash_key(KBJS_TYPES_STASH_KEY_LENGTH, kb_context->js_stash_key);

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* Set property-setters */
    /* STACK: [args..., this, "JSNAME"] */
    duk_push_string(context, "onActivate");
    /* STACK: [args..., this, "JSNAME", function] */
    duk_push_c_function(context, on_activate_setter, (duk_idx_t)1);
    /* STACK: [args..., this, "JSNAME", function, "setter"] */
    duk_push_string(context, "setter");
    /* STACK: [args..., this, "JSNAME", function] */
    duk_put_prop_string(context, (duk_idx_t)-2, "name");
    /* STACK: [args..., this] */
    duk_def_prop(context, (duk_idx_t)-3, DUK_DEFPROP_HAVE_SETTER);

    /* Create and store instance pointer */
    /* STACK: [args..., this, ""] */
    duk_push_string(context, KBJS_INSTANCE_PTR);
    /* STACK: [args..., this, "", void*] */
    duk_push_pointer(context, kb_context);
    /* STACK: [args..., this] */
    duk_put_prop(context, (duk_idx_t)-3);

    /* Create instance destructor */
    /* STACK: [args..., this, Context_del] */
    duk_push_c_function(context, kbjs_Context_del, (duk_idx_t)1);
    /* STACK: [args..., this] */
    duk_set_finalizer(context, (duk_idx_t)-2);

    /* Store `this` on stash */
    /* STACK: [args..., this, stash] */
    duk_push_heap_stash(context);
    /* STACK: [args..., this, stash, int] */
    duk_push_string(context, kb_context->js_stash_key);
    /* STACK: [args..., this, stash, int, this] */
    duk_dup(context, (duk_idx_t)-3);

    /* STACK: [args..., this, stash] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* STACK: [args..., this] */
    duk_pop(context);

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
    static const char *FUNC_NAME = "kb.rpi2.Context.stop()";

    /* STACK: [args..., this] */
    duk_push_this(context);

    /* STACK: [args..., this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_Context *kb_context = duk_get_pointer(context, (duk_idx_t)-1);

    /* Delete kibu Context instance */
    kb_Error kb_error;
    if ((kb_error = kb_rpi2_Context_stop((kb_rpi2_Context *const)kb_context)))
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
