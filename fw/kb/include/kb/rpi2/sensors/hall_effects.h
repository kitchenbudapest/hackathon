/* Header guard */
#ifndef KB_RPI2_SENSORS_HALL_EFFECTS_H_8053035005168279
#define KB_RPI2_SENSORS_HALL_EFFECTS_H_8053035005168279 1


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
#define KB_RPI2_SENSORS_HALL_EFFECT_MEMBERS()                                  \
    KB_RPI2_SENSOR_MEMBERS()                                                   \
    kb_Error (*on_magnetize)(struct kb_rpi2_sensors_hall_effect *const,        \
                             kb_rpi2_Event                      *const,        \
                             kb_rpi2_Context                    *const);       \
    kb_Error (*on_demagnetize)(struct kb_rpi2_sensors_hall_effect *const,      \
                               kb_rpi2_Event                      *const,      \
                               kb_rpi2_Context                    *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_hall_effect
{
    KB_RPI2_SENSORS_HALL_EFFECT_MEMBERS()
} kb_rpi2_sensors_HallEffect;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_HallEffect_new(kb_rpi2_sensors_HallEffect **const self,
                               kb_rpi2_Event               *const event,
                               kb_rpi2_PinId                      pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_HallEffect_ini(kb_rpi2_sensors_HallEffect *const self,
                               kb_rpi2_Event              *const event,
                               kb_rpi2_PinId                     pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_HallEffect_fin(kb_rpi2_sensors_HallEffect *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_HallEffect_del(kb_rpi2_sensors_HallEffect **const self);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_BIND_FUNCTION(STATE)            \
    kb_Error                                                                   \
    kb_rpi2_sensors_HallEffect_bind_on_##STATE(                                \
        kb_rpi2_sensors_HallEffect *const  self,                               \
        kb_Error (*on_##STATE)(kb_rpi2_sensors_HallEffect *const,              \
                               kb_rpi2_Event              *const,              \
                               kb_rpi2_Context            *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_BIND_FUNCTION(magnetize)
KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_BIND_FUNCTION(demagnetize)
#undef KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_BIND_FUNCTION


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_UNBIND_FUNCTION(STATE)          \
    kb_Error                                                                   \
    kb_rpi2_sensors_HallEffect_unbind_on_##STATE(                              \
        kb_rpi2_sensors_HallEffect *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_UNBIND_FUNCTION(magnetize)
KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_UNBIND_FUNCTION(demagnetize)
#undef KBJS_RPI2_SENSORS_HALL_EFFECT_ON_STATE_UNBIND_FUNCTION


#endif /* KB_RPI2_SENSORS_HALL_EFFECTS_H_8053035005168279 */
