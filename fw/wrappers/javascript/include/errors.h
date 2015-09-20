/* INFO **
** INFO */

/* Header guard */
#ifndef KBJS_ERRORS_H_1128492819178280
#define KBJS_ERRORS_H_1128492819178280 1

/*----------------------------------------------------------------------------*/
typedef enum
{
    kbjs_AllocationError = 1,
    kbjs_InternalError,
    kbjs_InvocationError,
    kbjs_ArgumentError,
    kbjs_ArgumentTypeError,
    kbjs_PropertyTypeError,
} kbjs_Error;


/*----------------------------------------------------------------------------*/
const char *
kbjs_Error_fmt(kbjs_Error error);

#endif /* KBJS_ERRORS_H_1128492819178280 */
