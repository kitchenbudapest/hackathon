/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_RGB_LED_H_4469568977430462
#define KB_RPI2_SENSORS_RGB_LED_H_4469568977430462 1


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    macro : kb_rpi2_SENSOR_MEMBERS */


/*----------------------------------------------------------------------------*/
#define KB_RPI2_SENSORS_RGB_LED_MEMBERS()                                      \
    KB_RPI2_SENSOR_MEMBERS()
    /* TODO: add callback members: on_green, on_yellow, etc.. */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_rgb_led
{
    KB_RPI2_SENSORS_RGB_LED_MEMBERS()
} kb_rpi2_sensors_RGBLED;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_new(kb_rpi2_sensors_RGBLED **const self,
                           kb_rpi2_Event           *const event,
                           kb_rpi2_PinId                  pin_red,
                           kb_rpi2_PinId                  pin_green,
                           kb_rpi2_PinId                  pin_blue);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_ini(kb_rpi2_sensors_RGBLED *const self,
                           kb_rpi2_Event          *const event,
                           kb_rpi2_PinId                 pin_red,
                           kb_rpi2_PinId                 pin_green,
                           kb_rpi2_PinId                 pin_blue);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_fin(kb_rpi2_sensors_RGBLED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_del(kb_rpi2_sensors_RGBLED **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KB_RPI2_SENSORS_RGB_LED_COLOR(COLOR)                                   \
    kb_Error                                                                   \
    kb_rpi2_sensors_RGBLED_##COLOR(kb_rpi2_sensors_RGBLED *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
KB_RPI2_SENSORS_RGB_LED_COLOR(red)
KB_RPI2_SENSORS_RGB_LED_COLOR(green)
KB_RPI2_SENSORS_RGB_LED_COLOR(blue)
KB_RPI2_SENSORS_RGB_LED_COLOR(yellow)
KB_RPI2_SENSORS_RGB_LED_COLOR(magenta)
KB_RPI2_SENSORS_RGB_LED_COLOR(cyan)
KB_RPI2_SENSORS_RGB_LED_COLOR(white)
KB_RPI2_SENSORS_RGB_LED_COLOR(black)
#undef KB_RPI2_SENSORS_RGB_LED_COLOR


#endif /* KB_RPI2_SENSORS_RGB_LED_H_4469568977430462 */
