/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_LEDS_H_8184762887585486__
#define __KB_RPI2_SENSORS_LEDS_H_8184762887585486__

/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_SENSOR_MEMBERS()
    kb_rpi2_PinId pin;
    kb_Error (*on_on)(kb_rpi2_Sensor*,
                      kb_rpi2_Event*,
                      kb_rpi2_Context*);
    kb_Error (*on_off)(kb_rpi2_Sensor*,
                       kb_rpi2_Event*,
                       kb_rpi2_Context*);
} kb_rpi2_Sensor_LED;


#endif /* __KB_RPI2_SENSORS_LEDS_H_8184762887585486__ */
