/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/errors.h"


/*----------------------------------------------------------------------------*/
static const char *const ERRORS[] =
{
    /* Reserved index by duktape */
    "(no error)\n",

    /* str: function name */
    "AllocationError: cannot allocate space for %s\n",

    /* str: error name
       str: function name */
    "InternalError: %s in function: %s\n",

    /* str: function name */
    "InvocationError: %s has to be called as constructor (with 'new')\n",

    /* str: function name
       int: arguments count expected
       int: arguments count got */
    "ArgumentError: %s expected %d arguments, but got: %d\n",

    /* str: function name
       str: argument type expected
       int: argument index
       str: argument type got */
    "ArgumentTypeError: %s expected %s at argument index %d, but got: %s\n",

    /* str: property name
       str: property type got */
    "PropertyTypeError: %s has to be a function, not: %s\n",
};



/*----------------------------------------------------------------------------*/
const char *
kbjs_Error_fmt(kbjs_Error error)
{
    switch (error)
    {
        case kbjs_AllocationError:
            return ERRORS[kbjs_AllocationError];

        case kbjs_InternalError:
            return ERRORS[kbjs_InternalError];

        case kbjs_InvocationError:
            return ERRORS[kbjs_InvocationError];

        case kbjs_ArgumentError:
            return ERRORS[kbjs_ArgumentError];

        case kbjs_ArgumentTypeError:
            return ERRORS[kbjs_ArgumentTypeError];

        case kbjs_PropertyTypeError:
            return ERRORS[kbjs_PropertyTypeError];

        default:
            return ERRORS[0];
    }
}
