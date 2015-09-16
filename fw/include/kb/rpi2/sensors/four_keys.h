/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__
#define __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    macro : kb_rpi2_SENSOR_MEMBERS */


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_SENSOR_MEMBERS()
    kb_Error (*on_key_1)(kb_rpi2_Sensor  *const,
                         kb_rpi2_Event   *const,
                         kb_rpi2_Context *const);
    kb_Error (*on_key_2)(kb_rpi2_Sensor  *const,
                         kb_rpi2_Event   *const,
                         kb_rpi2_Context *const);
    kb_Error (*on_key_3)(kb_rpi2_Sensor  *const,
                         kb_rpi2_Event   *const,
                         kb_rpi2_Context *const);
    kb_Error (*on_key_4)(kb_rpi2_Sensor  *const,
                         kb_rpi2_Event   *const,
                         kb_rpi2_Context *const);
} kb_rpi2_Sensor_LED;


#endif /* __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__ */
