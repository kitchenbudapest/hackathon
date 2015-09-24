/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <math.h>
/*  func  : fabs
            floor */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include unix headers */
#if __STDC_VERSION__ >= 199901L
    #define __USE_POSIX199309
#endif /* __STDC_VERSION__ */
#include <time.h>
/*  type  : struct timespec
    func  : nanosleep */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_context
            duk_ret_t
            duk_idx_t
            duk_errcode_t
    func  : duk_pop
            duk_error
            duk_push_global_object
            duk_push_string
            duk_push_c_function
            duk_put_prop
            duk_safe_to_string
            duk_get_number
            duk_is_nan */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/errors.h"
/*  const : kbjs_ArgumentTypeError
            kbjs_LongOverflowError
    func  : kbjs_Error_fmt */

/*----------------------------------------------------------------------------*/
static long int S_TO_MS                  = 1000L;
static long int MS_TO_NS                 = 1000000L;
static const char *const SLEEP_FUNC_NAME = "sleep";


/*----------------------------------------------------------------------------*/
static duk_ret_t
kbjs_sleep(duk_context *context)
{
    /* Check if first argument is a number */
    /* STACK: [..., interval] */
    if (duk_is_nan(context, (duk_idx_t)-1))
        duk_error(context,
                  (duk_errcode_t)kbjs_ArgumentTypeError,
                  kbjs_Error_fmt(kbjs_ArgumentTypeError),
                  SLEEP_FUNC_NAME,
                  "Number",
                  0,
                  duk_safe_to_string(context, (duk_idx_t)-1));

    /* Get first argument as integer in miliseconds */
    long ms = (long)floor(fabs(duk_get_number(context, (duk_idx_t)-1)));
    long s  = ms / S_TO_MS;

    /* Sleep this thread */
    struct timespec interval =
    {
        (time_t)s,
        (ms - s*S_TO_MS)*MS_TO_NS
    };

    nanosleep(&interval, NULL);

    return (duk_ret_t)0;
}


/*----------------------------------------------------------------------------*/
void
kbjs_register_built_ins(duk_context *context)
{
    /* STACK: [..., global] */
    duk_push_global_object(context);
    /* STACK: [..., global, "sleep"] */
    duk_push_string(context, SLEEP_FUNC_NAME);
    /* STACK: [..., global, "sleep", function] */
    duk_push_c_function(context, kbjs_sleep, (duk_idx_t)1);
    /* STACK: [..., global] */
    duk_put_prop(context, (duk_idx_t)-3);
    /* STACK: [...] */
    duk_pop(context);
}
