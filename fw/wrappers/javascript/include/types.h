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
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId */
#include <kb/rpi2/types.h>
/*  macro : KB_RPI2_CONTEXT_MEMBERS
            KB_RPI2_EVENT_MEMBERS */
#include <kb/rpi2/sensors/leds.h>
/*  macro : KB_RPI2_SENSORS_LED_MEMBERS */


/*----------------------------------------------------------------------------*/
/* Helper function */
int
kbjs_get_stash_key(size_t  length,
                   char   *buffer);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_TYPES_STASH_KEY_LENGTH (size_t)16
#define KBJS_TYPES_MEMBERS()                                                   \
    duk_context *js_context;                                                   \
    char         js_stash_key[KBJS_TYPES_STASH_KEY_LENGTH];

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


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_PinId id;
    const char    str[(size_t)16];
    KBJS_TYPES_MEMBERS()
} kbjs_PinId;


/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_RPI2_SENSORS_LED_MEMBERS()
    KBJS_TYPES_MEMBERS()
} kbjs_LED;


#undef KBJS_TYPES_MEMBERS
#endif /* KBJS_TYPES_H_6530818369583821 */
