/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE */
#include <stdio.h>
/*  const : stderr
    func  : fputs */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_context
    func  : duk_create_heap_default
            duk_push_global_object
            duk_push_string
            duk_push_object
            duk_put_prop
            duk_pop
            duk_eval_file
            duk_destroy_heap */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/contexts.h"
/*  func  : kbjs_register_Context */


/*----------------------------------------------------------------------------*/
int
main(int argc,
     char const *argv[])
{
    /* If no file path passed */
    if (argc < 2)
    {
        fputs("kbjs: File path missing (first argument)\n", stderr);
        return EXIT_FAILURE;
    }

    /* Create duktape heap */
    duk_context *context;
    if (!(context = duk_create_heap_default()))
    {
        fputs("kbjs: Internal allocation failed, during "
              "the creation of the duktape heap\n", stderr);
        return EXIT_FAILURE;
    }

    /* Create modul objects */
    duk_push_global_object(context);
    duk_push_string(context, "kb");
    duk_push_object(context);
    duk_push_string(context, "rpi2");
    duk_push_object(context);
    duk_put_prop(context, -3);
    duk_put_prop(context, -3);
    duk_pop(context);

    /* Load kbjs modules */
    kbjs_register_Context(context);
    // kbjs_register_Event(context);
    // kbjs_register_LED(context);
    // kbjs_register_FourKeys(context);

    /* Evaluate passed script */
    duk_eval_file(context, argv[1]);

    /* Clean up and terminate */
    duk_destroy_heap(context);
    return EXIT_SUCCESS;
}
