/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_LEDS_H_8184762887585486
#define KB_RPI2_SENSORS_LEDS_H_8184762887585486 1


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
typedef struct kb_rpi2_sensors_led
{
    KB_RPI2_SENSOR_MEMBERS()
    kb_Error (*on_on)(struct kb_rpi2_sensors_led *const,
                      kb_rpi2_Event              *const,
                      kb_rpi2_Context            *const);
    kb_Error (*on_off)(struct kb_rpi2_sensors_led *const,
                       kb_rpi2_Event              *const,
                       kb_rpi2_Context            *const);
} kb_rpi2_sensors_LED;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_new(kb_rpi2_sensors_LED **const self,
                        kb_rpi2_Event        *const event,
                        kb_rpi2_PinId               pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_ini(kb_rpi2_sensors_LED *const self,
                        kb_rpi2_Event       *const event,
                        kb_rpi2_PinId              pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_fin(kb_rpi2_sensors_LED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_del(kb_rpi2_sensors_LED **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_on(kb_rpi2_sensors_LED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_off(kb_rpi2_sensors_LED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_bind_on_on(kb_rpi2_sensors_LED *const self,
                               kb_Error (*on_on)(kb_rpi2_sensors_LED *const,
                                                 kb_rpi2_Event       *const,
                                                 kb_rpi2_Context     *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_unbind_on_on(kb_rpi2_sensors_LED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_bind_on_off(kb_rpi2_sensors_LED *const self,
                                kb_Error (*on_off)(kb_rpi2_sensors_LED *const,
                                                   kb_rpi2_Event       *const,
                                                   kb_rpi2_Context     *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_unbind_on_off(kb_rpi2_sensors_LED *const self);


#endif /* KB_RPI2_SENSORS_LEDS_H_8184762887585486 */
