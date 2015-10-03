/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_BUTTONS_H_7318080831399207
#define KB_RPI2_SENSORS_BUTTONS_H_7318080831399207 1


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
#define KB_RPI2_SENSORS_BUTTON_MEMBERS()                                       \
    KB_RPI2_SENSOR_MEMBERS()                                                   \
    kb_Error (*on_press)(struct kb_rpi2_sensors_button *const,                 \
                         kb_rpi2_Event                 *const,                 \
                         kb_rpi2_Context               *const);                \
    kb_Error (*on_release)(struct kb_rpi2_sensors_button *const,               \
                           kb_rpi2_Event                 *const,               \
                           kb_rpi2_Context               *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_button
{
    KB_RPI2_SENSORS_BUTTON_MEMBERS()
} kb_rpi2_sensors_Button;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_Button_new(kb_rpi2_sensors_Button **const self,
                           kb_rpi2_Event           *const event,
                           kb_rpi2_PinId                  pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_ini(kb_rpi2_sensors_Button *const self,
                               kb_rpi2_Event      *const event,
                               kb_rpi2_PinId             pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_fin(kb_rpi2_sensors_Button *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_del(kb_rpi2_sensors_Button **const self);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_BIND_FUNCTION(STATE)                \
    kb_Error                                                                   \
    kb_rpi2_sensors_Button_bind_on_##STATE(                                    \
        kb_rpi2_sensors_Button *const  self,                                   \
        kb_Error (*on_##STATE)(kb_rpi2_sensors_Button *const,                  \
                               kb_rpi2_Event          *const,                  \
                               kb_rpi2_Context        *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_BIND_FUNCTION(press)
KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_BIND_FUNCTION(release)
#undef KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_BIND_FUNCTION


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_UNBIND_FUNCTION(STATE)              \
    kb_Error                                                                   \
    kb_rpi2_sensors_Button_unbind_on_##STATE(                                  \
        kb_rpi2_sensors_Button *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_UNBIND_FUNCTION(press)
KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_UNBIND_FUNCTION(release)
#undef KBJS_RPI2_SENSORS_BUTTONS_ON_STATE_UNBIND_FUNCTION


#endif /* KB_RPI2_SENSORS_BUTTONS_H_7318080831399207 */
