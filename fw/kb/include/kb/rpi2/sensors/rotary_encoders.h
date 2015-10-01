/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_ROTARY_ENCODER_H_0871794195935062
#define KB_RPI2_SENSORS_ROTARY_ENCODER_H_0871794195935062 1

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
#define KB_RPI2_SENSORS_ROTARY_ENCODER_MEMBERS()                               \
    KB_RPI2_SENSOR_MEMBERS()                                                   \
    kb_Error (*on_click)(                                                      \
        struct kb_rpi2_sensors_rotary_encoder *const,                          \
        kb_rpi2_Event                         *const,                          \
        kb_rpi2_Context                       *const);                         \
    kb_Error (*on_rotate_clock_wise)(                                          \
        struct kb_rpi2_sensors_rotary_encoder *const,                          \
        kb_rpi2_Event                         *const,                          \
        kb_rpi2_Context                       *const);                         \
    kb_Error (*on_rotate_counter_clock_wise)(                                  \
        struct kb_rpi2_sensors_rotary_encoder *const,                          \
        kb_rpi2_Event                         *const,                          \
        kb_rpi2_Context                       *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_rotary_encoder
{
    KB_RPI2_SENSORS_ROTARY_ENCODER_MEMBERS()
} kb_rpi2_sensors_RotaryEncoder;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_new(kb_rpi2_sensors_RotaryEncoder **const self,
                                  kb_rpi2_Event                  *const event,
                                  kb_rpi2_PinId                         pin_switch,
                                  kb_rpi2_PinId                         pin_data,
                                  kb_rpi2_PinId                         pin_clock);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_ini(kb_rpi2_sensors_RotaryEncoder *const self,
                                  kb_rpi2_Event                 *const event,
                                  kb_rpi2_PinId                        pin_switch,
                                  kb_rpi2_PinId                        pin_data,
                                  kb_rpi2_PinId                        pin_clock);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_fin(kb_rpi2_sensors_RotaryEncoder *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_del(kb_rpi2_sensors_RotaryEncoder **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_click(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_click)(kb_rpi2_sensors_RotaryEncoder *const,
                         kb_rpi2_Event                 *const,
                         kb_rpi2_Context               *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_click(
    kb_rpi2_sensors_RotaryEncoder *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_rotate_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_rotate_clock_wise)(kb_rpi2_sensors_RotaryEncoder *const,
                                     kb_rpi2_Event                 *const,
                                     kb_rpi2_Context               *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_rotate_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_rotate_counter_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_rotate_counter_clock_wise)(kb_rpi2_sensors_RotaryEncoder *const,
                                             kb_rpi2_Event                 *const,
                                             kb_rpi2_Context               *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_rotate_counter_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self);


#endif /* KB_RPI2_SENSORS_ROTARY_ENCODER_H_0871794195935062 */
