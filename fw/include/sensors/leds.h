/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_LEDS_H_8184762887585486__
#define __KB_RPI2_SENSORS_LEDS_H_8184762887585486__

/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_RPi2_SENSOR_MEMBERS()
    kb_RPi2_PinId pin;
    kb_Error (*on_on)(kb_RPi2_Sensor*,
                      kb_RPi2_Event*,
                      kb_RPi2_Context*);
    kb_Error (*on_off)(kb_RPi2_Sensor*,
                       kb_RPi2_Event*,
                       kb_RPi2_Context*);
} kb_RPi2_Sensor_LED;


#endif /* __KB_RPI2_SENSORS_LEDS_H_8184762887585486__ */
