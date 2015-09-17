/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : puts */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include "duktape.h"
/*  type  : duk_ret_t
            duk_errcode_t
            duk_context
    func  : duk_fatal
            duk_require_string */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include project headers */
#include "type.h"
/*  type  : E
            T
    func  : T_new
            T_del
            T_str
    const : OKAY
            SELF_IS_NULL
            ARG2_IS_NULL
            ALLOC_FAIL */


/*----------------------------------------------------------------------------*/
/* Forward declarations */
static duk_ret_t
js_T_new(duk_context *context);
static duk_ret_t
js_T_del(duk_context *context);
static duk_ret_t
js_T_str(duk_context *context);

#define HIDDEN_PROPERTY "\xFF\xFF"
#define INSTANCE_PTR    HIDDEN_PROPERTY "instance_ptr"


/*----------------------------------------------------------------------------*/
static duk_ret_t
js_T_new(duk_context *context)
{
    const char *name = duk_require_string(context, 0);
    T *t;
    switch (T_new(&t, name))
    {
        case ALLOC_FAIL:
            duk_fatal(context,
                      (duk_errcode_t)ALLOC_FAIL,
                      "T: internal allocation failed");
            return 0;

        default:
            puts("==> T: new()");
            duk_push_this(context);

            printf("  <- (new) Stored instance_ptr: %p\n", t);

            duk_push_pointer(context, (void *)t);
            duk_put_prop_string(context, -2, INSTANCE_PTR);

            duk_push_c_function(context, js_T_del, 0);
            duk_set_finalizer(context, -2);
            return 1;
    }
}


/*----------------------------------------------------------------------------*/
static duk_ret_t
js_T_del(duk_context *context)
{
    puts("==> T: del()");

    duk_get_prop_string(context, 0, INSTANCE_PTR);

    /*
     * <<<<<<<<<<<< For some reason, the rest of this function is not called!
     *              Check the return values/errors of the duk_* functions!
     */

    T *t = duk_to_pointer(context, -1);

    printf("  -> (del) Accessed instance_ptr: %p\n", t);

    T_del(&t);
    return 0;
}


/*----------------------------------------------------------------------------*/
static duk_ret_t
js_T_str(duk_context *context)
{
    puts("==> T: str()");
    duk_push_this(context);
    duk_get_prop_string(context, -1, INSTANCE_PTR);
    T *t = duk_to_pointer(context, -1);

    printf("  -> (str) Accessed instance_ptr: %p\n", t);

    char *name;

    /*
     * FIXME: If `print(T.prototype)` is called name is pointing at garbage.
     *        This conditional is a dirty quick fix, but it needs a reliable,
     *        stable and safe solution.
     */
    if (t)
        T_str(t, &name);
    else
        name = "";

    duk_push_sprintf(context, "[object T {name: %s}]", name);
    return 1;
}


/*----------------------------------------------------------------------------*/
const duk_function_list_entry js_T_methods[] =
{
    {"toString", js_T_str, 0},
    {NULL      , NULL    , 0},
};


/*----------------------------------------------------------------------------*/
void
js_register_T(duk_context *context)
{
    duk_push_global_object(context);
    duk_push_c_function(context, js_T_new, 1);

    duk_push_object(context);
    duk_put_function_list(context, 2, js_T_methods);
    duk_put_prop_string(context, 1, "prototype");

    duk_put_global_string(context, "T");
    duk_pop(context);
}
