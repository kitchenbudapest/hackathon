/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_ULTRASONIC_SENSORS_H_9775452237672786
#define KB_RPI2_SENSORS_ULTRASONIC_SENSORS_H_9775452237672786 1


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
#define KB_RPI2_SENSORS_ULTRASONIC_SENSOR_MEMBERS()                            \
    KB_RPI2_SENSOR_MEMBERS()
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_ultrasonic_sensor
{
    KB_RPI2_SENSORS_ULTRASONIC_SENSOR_MEMBERS()
} kb_rpi2_sensors_UltrasonicSensor;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_new(
    kb_rpi2_sensors_UltrasonicSensor **const self,
    kb_rpi2_Event                     *const event,
    kb_rpi2_PinId                            pin_echo,
    kb_rpi2_PinId                            pin_trigger);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_ini(
    kb_rpi2_sensors_UltrasonicSensor *const self,
    kb_rpi2_Event                    *const event,
    kb_rpi2_PinId                           pin_echo,
    kb_rpi2_PinId                           pin_trigger);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_fin(
    kb_rpi2_sensors_UltrasonicSensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_del(
    kb_rpi2_sensors_UltrasonicSensor **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_measure(
    kb_rpi2_sensors_UltrasonicSensor *const  self,
    double                                  *distance);


#endif /* KB_RPI2_SENSORS_ULTRASONIC_SENSORS_H_9775452237672786 */
