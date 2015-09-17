/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__
#define __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    macro : kb_rpi2_SENSOR_MEMBERS */


/*----------------------------------------------------------------------------*/
typedef struct kb_rpi2_sensors_four_keys
{
    KB_RPI2_SENSOR_MEMBERS()
    kb_Error (*on_key_1)(struct kb_rpi2_sensors_four_keys *const,
                         kb_rpi2_Event                    *const,
                         kb_rpi2_Context                  *const);
    kb_Error (*on_key_2)(struct kb_rpi2_sensors_four_keys *const,
                         kb_rpi2_Event                    *const,
                         kb_rpi2_Context                  *const);
    kb_Error (*on_key_3)(struct kb_rpi2_sensors_four_keys *const,
                         kb_rpi2_Event                    *const,
                         kb_rpi2_Context                  *const);
    kb_Error (*on_key_4)(struct kb_rpi2_sensors_four_keys *const,
                         kb_rpi2_Event                    *const,
                         kb_rpi2_Context                  *const);
} kb_rpi2_sensors_FourKeys;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_new(kb_rpi2_sensors_FourKeys **const self,
                             kb_rpi2_Event             *const event,
                             kb_rpi2_PinId                    pin_row,
                             kb_rpi2_PinId                    pin_col1,
                             kb_rpi2_PinId                    pin_col2,
                             kb_rpi2_PinId                    pin_col3,
                             kb_rpi2_PinId                    pin_col4);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_ini(kb_rpi2_sensors_FourKeys *const self,
                             kb_rpi2_Event            *const event,
                             kb_rpi2_PinId                   pin_row,
                             kb_rpi2_PinId                   pin_col1,
                             kb_rpi2_PinId                   pin_col2,
                             kb_rpi2_PinId                   pin_col3,
                             kb_rpi2_PinId                   pin_col4);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_fin(kb_rpi2_sensors_FourKeys *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_del(kb_rpi2_sensors_FourKeys **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION(KEY)                  \
    kb_Error                                                                   \
    kb_rpi2_sensors_FourKeys_bind_on_key_##KEY(                                \
        kb_rpi2_sensors_FourKeys *const  self,                                 \
        kb_Error (*on_key_##KEY)(kb_rpi2_sensors_FourKeys *const,              \
                                 kb_rpi2_Event            *const,              \
                                 kb_rpi2_Context          *const));
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION(1)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION(2)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION(3)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION(4)
#undef KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_BIND_FUNCTION
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION(KEY)                \
    kb_Error                                                                   \
    kb_rpi2_sensors_FourKeys_unbind_on_key_##KEY(                              \
        kb_rpi2_sensors_FourKeys *const  self,                                 \
        kb_Error (*on_key_##KEY)(kb_rpi2_sensors_FourKeys *const,              \
                                 kb_rpi2_Event            *const,              \
                                 kb_rpi2_Context          *const));
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION(1)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION(2)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION(3)
KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION(4)
#undef KB_RPI2_SENSORS_FOUR_KEYS_ON_KEY_X_UNBIND_FUNCTION


#endif /* __KB_RPI2_SENSORS_FOUR_KEYS_H_49359163029359965__ */
