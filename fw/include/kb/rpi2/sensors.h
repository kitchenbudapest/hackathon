/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_SENSORS_H_24463479806314148__
#define __KB_RPI2_SENSORS_H_24463479806314148__


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
kb_rpi2_Sensor_new(kb_rpi2_Sensor **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_ini(kb_rpi2_Sensor *const self,
                   kb_rpi2_Event  *const event,
                   size_t         *const pin_id_count,
                   kb_rpi2_PinId  *const pin_ids);
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
kb_rpi2_Sensor_bind_pin(kb_rpi2_Sensor *const self,
                        kb_rpi2_Pin    *const pin);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_unbind_pin(kb_rpi2_Sensor *const self,
                          kb_rpi2_Pin    *const pin);


#endif /* __KB_RPI2_SENSORS_H_24463479806314148__ */
