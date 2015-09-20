/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include duktape headers */
#include <duktape.h>
/*  type  : duk_idx_t */

/*----------------------------------------------------------------------------*/
static const char *const T_NONE      = "(none)";
static const char *const T_UNDEFINED = "undefined";
static const char *const T_NULL      = "null";
static const char *const T_BOOLEAN   = "boolean";
static const char *const T_NUMBER    = "number";
static const char *const T_STRING    = "string";
static const char *const T_OBJECT    = "object";
static const char *const T_BUFFER    = "buffer";
static const char *const T_POINTER   = "pointer";
static const char *const T_LIGHTFUNC = "light-function";


/*----------------------------------------------------------------------------*/
const char *
kbjs_js_types_str(duk_idx_t type)
{
    switch (type)
    {
        case DUK_TYPE_UNDEFINED:
            return T_UNDEFINED;
        case DUK_TYPE_NULL:
            return T_NULL;
        case DUK_TYPE_BOOLEAN:
            return T_BOOLEAN;
        case DUK_TYPE_NUMBER:
            return T_NUMBER;
        case DUK_TYPE_STRING:
            return T_STRING;
        case DUK_TYPE_OBJECT:
            return T_OBJECT;
        case DUK_TYPE_BUFFER:
            return T_BUFFER;
        case DUK_TYPE_POINTER:
            return T_POINTER;
        case DUK_TYPE_LIGHTFUNC:
            return T_LIGHTFUNC;
        default:
            return T_NONE;
    }
}
