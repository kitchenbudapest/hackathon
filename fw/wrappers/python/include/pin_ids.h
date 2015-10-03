/* INFO **
** INFO */

#ifndef KBPY_RPI2_PIN_IDS_H_9242966325654632
#define KBPY_RPI2_PIN_IDS_H_9242966325654632 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/enums.h>
/*  const : kb_rpi2_PINS_COUNT */


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_PinId  id;
    const char    *name;
} kbpy_rpi2_PyPinId;


/*----------------------------------------------------------------------------*/
const kbpy_rpi2_PyPinId kbpy_rpi2_PY_PIN_IDS[kb_rpi2_PINS_COUNT];


#endif /* KBPY_RPI2_PIN_IDS_H_9242966325654632 */
