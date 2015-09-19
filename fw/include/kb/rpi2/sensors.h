/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_H_24463479806314148
#define KB_RPI2_SENSORS_H_24463479806314148 1


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Pin
            kb_rpi2_Sensor
            kb_rpi2_Event
            kb_rpi2_Context */

/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Sensor_new(kb_rpi2_Sensor   **const self,
                   kb_rpi2_Event     *const event,
                   size_t                   pins_count,
                   kb_rpi2_PinId     *const pin_ids,
                   kb_rpi2_PinRole   *const pin_roles,
                   kb_rpi2_PinState  *const pin_states);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_ini(kb_rpi2_Sensor   *const self,
                   kb_rpi2_Event    *const event,
                   size_t                  pins_count,
                   kb_rpi2_PinId    *const pin_ids,
                   kb_rpi2_PinRole  *const pin_roles,
                   kb_rpi2_PinState *const pin_states);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_fin(kb_rpi2_Sensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_del(kb_rpi2_Sensor **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_callback_args(kb_rpi2_Sensor   *const self,
                             kb_rpi2_Event   **const event,
                             kb_rpi2_Context **const context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_enable(kb_rpi2_Sensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_disable(kb_rpi2_Sensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_bind_on_enable(kb_rpi2_Sensor *const   self,
                              kb_Error (*on_enable)(kb_rpi2_Sensor  *const,
                                                    kb_rpi2_Event   *const,
                                                    kb_rpi2_Context *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_unbind_on_enable(kb_rpi2_Sensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_bind_on_disable(kb_rpi2_Sensor *const   self,
                              kb_Error (*on_disable)(kb_rpi2_Sensor *const,
                                                    kb_rpi2_Event   *const,
                                                    kb_rpi2_Context *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_unbind_on_disable(kb_rpi2_Sensor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_get_pin(kb_rpi2_Sensor  *const self,
                       size_t                 pin_index,
                       kb_rpi2_Pin    **const pin);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_listen_all_pins(kb_rpi2_Sensor *const self);


#endif /* KB_RPI2_SENSORS_H_24463479806314148 */
