/* INFO **
** INFO */

/* Header guard */
#ifndef KBPY_ERRORS_H_2351458495504491
#define KBPY_ERRORS_H_2351458495504491 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject */

/*----------------------------------------------------------------------------*/
typedef enum
{
    kbpy_FAIL = -1,
    kbpy_OKAY,
} kbpy_PythonReturnValues;


/*----------------------------------------------------------------------------*/
extern PyObject *kbpy_rpi2_INTERNAL_ERROR;


#endif /* KBPY_ERRORS_H_2351458495504491 */
