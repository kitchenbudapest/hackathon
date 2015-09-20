/* INFO **
** INFO */

/* Header guards */
#ifndef KBJS_TYPES_H_6530818369583821
#define KBJS_TYPES_H_6530818369583821 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_context
            duk_ret_t
            duk_idx_t
            duk_function_list_entry */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/types.h>
/*  macro : KB_RPI2_CONTEXT_MEMBERS
            KB_RPI2_EVENT_MEMBERS */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_TYPES_MEMBERS()                                                   \
    duk_context *js_context;

/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_RPI2_CONTEXT_MEMBERS()
    KBJS_TYPES_MEMBERS()
} kbjs_Context;


/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_RPI2_EVENT_MEMBERS()
    KBJS_TYPES_MEMBERS()
} kbjs_Event;

#undef KBJS_TYPES_MEMBERS

#endif /* KBJS_TYPES_H_6530818369583821 */
