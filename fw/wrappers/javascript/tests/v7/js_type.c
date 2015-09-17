/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : puts */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include v7 headers */
#include "external/include/v7.h"
/*  type  : struct v7
            v7_val_t
    func  : v7_create_object
            v7_create_constructor
            v7_set
            v7_array_get
            v7_get_global_object
            v7_to_string
            v7_create_null */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include project headers */
#include "type.h"
/*  macro : JS_TYPE_NAME_SIZE
    type  : T
            E
    func  : T_new
            T_del
            T_str */
#include "js_type.h"
/**/

static T *t = NULL;

static v7_val_t
js_T_new(struct v7 *context,
         v7_val_t   this,
         v7_val_t   args)
{
    v7_val_t name = v7_array_get(context, args, 0ul);

    size_t len;
    if (T_new(&t, v7_to_string(context, &name, &len)))
        v7_throw(context, "js_T_new(): Allocation failed");

    v7_set(context, this, "fuck", ~0, 0, v7_create_number(13));

    return this;
}

static v7_val_t
js_T_str(struct v7 *context,
         v7_val_t   this,
         v7_val_t   args)
{
    (void)this;
    (void)args;
    char *name;
    if (T_str(t, &name))
        return v7_create_null();
    return v7_create_string(context, name, ~0, 0);
}

void
create_T(struct v7 *context)
{
    v7_val_t T_proto = v7_create_object(context);
    v7_val_t T_constructor =
        v7_create_constructor(context, T_proto, js_T_new, 1);
    v7_set_method(context, T_proto, "toString", js_T_str);

    int xxx;
    if ((xxx = v7_set(context, v7_get_global_object(context), "T", ~0, 0, T_proto)))
    {
        printf("[0] Error(%d): v7_set()", xxx);
        return;
    }
}
