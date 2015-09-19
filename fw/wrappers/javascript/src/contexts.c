/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_context
            duk_ret_t */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include project headers */
// #include <kb/rpi2/contexts.h>
/**/

/*----------------------------------------------------------------------------*/
static duk_ret_t
kbjs_Context_new(duk_context *context)
{
    duk_push_this(context);
    return 0;
}


/*----------------------------------------------------------------------------*/
void
kbjs_register_Context(duk_context *context)
{
    duk_push_global_object(context);
    duk_get_prop_string(context, -1, "kb");
    duk_get_prop_string(context, -1, "rpi2");

    duk_push_string(context, "Context");
    duk_push_c_function(context, kbjs_Context_new, 0);
    duk_put_prop(context, -3);

    duk_pop_3(context);
}
