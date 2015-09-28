/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_PHOTO_RESISTOR_H_2917164161913199
#define KB_RPI2_SENSORS_PHOTO_RESISTOR_H_2917164161913199 1

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
#define KB_RPI2_SENSORS_PHOTO_RESISTOR_MEMBERS()                               \
    KB_RPI2_SENSOR_MEMBERS()                                                   \
    kb_Error (*on_light)(struct kb_rpi2_sensors_photo_resistor *const,         \
                         kb_rpi2_Event                         *const,         \
                         kb_rpi2_Context                       *const);        \
    kb_Error (*on_dark)(struct kb_rpi2_sensors_photo_resistor *const,          \
                        kb_rpi2_Event                         *const,          \
                        kb_rpi2_Context                       *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_photo_resistor
{
    KB_RPI2_SENSORS_PHOTO_RESISTOR_MEMBERS()
} kb_rpi2_sensors_PhotoResistor;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_new(kb_rpi2_sensors_PhotoResistor **const self,
                                  kb_rpi2_Event                  *const event,
                                  kb_rpi2_PinId                         pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_ini(kb_rpi2_sensors_PhotoResistor *const self,
                                  kb_rpi2_Event                 *const event,
                                  kb_rpi2_PinId                        pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_fin(kb_rpi2_sensors_PhotoResistor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_del(kb_rpi2_sensors_PhotoResistor **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_bind_on_light(
    kb_rpi2_sensors_PhotoResistor *const  self,
    kb_Error (*on_light)(kb_rpi2_sensors_PhotoResistor *const,
                        kb_rpi2_Event                 *const,
                        kb_rpi2_Context               *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_unbind_on_light(
    kb_rpi2_sensors_PhotoResistor *const  self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_bind_on_dark(
    kb_rpi2_sensors_PhotoResistor *const  self,
    kb_Error (*on_dark)(kb_rpi2_sensors_PhotoResistor *const,
                         kb_rpi2_Event                 *const,
                         kb_rpi2_Context               *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_PhotoResistor_unbind_on_dark(
    kb_rpi2_sensors_PhotoResistor *const  self);


#endif /* KB_RPI2_SENSORS_PHOTO_RESISTOR_H_2917164161913199 */
