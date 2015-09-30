/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_MOTION_SENSORS_H_2366513841514091
#define KB_RPI2_SENSORS_MOTION_SENSORS_H_2366513841514091 1


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
#define KB_RPI2_SENSORS_MOTION_SENSOR_MEMBERS()                                \
    KB_RPI2_SENSOR_MEMBERS()                                                   \
    kb_Error (*on_motion)(struct kb_rpi2_sensors_motion_sensor *const,         \
                          kb_rpi2_Event                        *const,         \
                          kb_rpi2_Context                      *const);        \
    kb_Error (*on_still)(struct kb_rpi2_sensors_motion_sensor *const,          \
                         kb_rpi2_Event                        *const,          \
                         kb_rpi2_Context                      *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_motion_sensor
{
    KB_RPI2_SENSORS_MOTION_SENSOR_MEMBERS()
} kb_rpi2_sensors_MotionSensor;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_MotionSensor_new(kb_rpi2_sensors_MotionSensor **const self,
                                 kb_rpi2_Event                 *const event,
                                 kb_rpi2_PinId                        pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_MotionSensor_ini(kb_rpi2_sensors_MotionSensor *const self,
                                 kb_rpi2_Event                *const event,
                                 kb_rpi2_PinId                       pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_MotionSensor_fin(kb_rpi2_sensors_MotionSensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_MotionSensor_del(kb_rpi2_sensors_MotionSensor **const self);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_BIND_FUNCTION(STATE)          \
    kb_Error                                                                   \
    kb_rpi2_sensors_MotionSensor_bind_on_##STATE(                              \
        kb_rpi2_sensors_MotionSensor *const  self,                             \
        kb_Error (*on_##STATE)(kb_rpi2_sensors_MotionSensor *const,            \
                               kb_rpi2_Event                *const,            \
                               kb_rpi2_Context              *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_BIND_FUNCTION(motion)
KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_BIND_FUNCTION(still)
#undef KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_BIND_FUNCTION


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_UNBIND_FUNCTION(STATE)        \
    kb_Error                                                                   \
    kb_rpi2_sensors_MotionSensor_unbind_on_##STATE(                            \
        kb_rpi2_sensors_MotionSensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_UNBIND_FUNCTION(motion)
KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_UNBIND_FUNCTION(still)
#undef KBJS_RPI2_SENSORS_MOTION_SENSOR_ON_STATE_UNBIND_FUNCTION



#endif /* KB_RPI2_SENSORS_MOTION_SENSORS_H_2366513841514091 */
