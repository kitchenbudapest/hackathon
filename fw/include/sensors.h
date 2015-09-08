/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_H_24463479806314148__
#define __KB_RPI2_SENSORS_H_24463479806314148__

/* Include kibu headers */
#include <kb/errors.h> /*
    type  : kb_Error
    const : kb_OKAY
*/

/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Sensor_ENABLED,
    kb_rpi2_Sensor_DISABLED,
} kb_rpi2_SensorState;


/*----------------------------------------------------------------------------*/
#define kb_rpi2_SENSOR_MEMBERS()                                               \
    kb_rpi2_Event       *event;                                                \
    kb_rpi2_SensorState  state;                                                \
    kb_rpi2_PinArray    *pins;                                                 \
    kb_Error           (*on_enable)(kb_rpi2_Sensor*,                           \
                                    kb_rpi2_Event*,                            \
                                    kb_rpi2_Context*);                         \
    kb_Error           (*on_disable)(kb_rpi2_Sensor*,                          \
                                     kb_rpi2_Event*,                           \
                                     kb_rpi2_Context*);



/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_SENSOR_MEMBERS()
} kb_rpi2_Sensor;

#endif /* __KB_RPI2_SENSORS_H_24463479806314148__ */