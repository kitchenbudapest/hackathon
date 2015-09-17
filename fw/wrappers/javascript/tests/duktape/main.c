/* INFO **
** INFO */

#include <stdio.h>
#include <stdlib.h>
#include "duktape.h"
#include "js_type.h"

int
main(void)
{
    duk_context *context = duk_create_heap_default();
    if (!context)
    {
        puts("duk: heap creation failed");
        return EXIT_FAILURE;
    }

    js_register_T(context);
    duk_eval_file(context, "main.js");

    duk_destroy_heap(context);
    return EXIT_SUCCESS;
}
