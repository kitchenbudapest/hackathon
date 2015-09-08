/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_PINS_H_15777440527397069__
#define __KB_RPI2_PINS_H_15777440527397069__


/* Include kibu headers */
#include <kb/errors.h> /*
    type  : kb_Error
*/

#include <kb/RPi2/sensors.h> /*
    type  : kb_rpi2_Sensor
*/

#include <kb/RPi2/events.h> /*
    type  : kb_rpi2_Event
*/

#include <kb/RPi2/contexts.h> /*
    type  : kb_rpi2_Context
*/


/*----------------------------------------------------------------------------*/
#define kb_rpi2_PIN_COUNT 40

/*----------------------------------------------------------------------------*/
void
kb_rpi2_print_pin_layout(void);


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Pin_LOW  = 0,
    kb_rpi2_Pin_HIGH = 1,
} kb_rpi2_PinState;


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_PIN1,
    kb_rpi2_PIN2,
    kb_rpi2_PIN3,
} kb_rpi2_PinId;


/*----------------------------------------------------------------------------*/
typedef struct
{
    /* Static data */
    kb_rpi2_PinId    id;
    kb_rpi2_PinState state;
    kb_rpi2_Sensor   sensor;

    /* Available callbacks */
    kb_Error      (*on_high)(kb_rpi2_Pin*,
                             kb_rpi2_Sensor*,
                             kb_rpi2_Event*,
                             kb_rpi2_Context*);
    kb_Error      (*on_low)(kb_rpi2_Pin*,
                            kb_rpi2_Sensor*,
                            kb_rpi2_Event*,
                            kb_rpi2_Context*);
} kb_rpi2_Pin;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_new(kb_rpi2_Pin   **self,
                kb_rpi2_PinId   pin_id,
                kb_rpi2_Sensor *sensor);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_del(kb_rpi2_Pin **self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_reset(kb_rpi2_Pin *self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_high(kb_rpi2_Pin *self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_low(kb_rpi2_Pin *self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_high(kb_rpi2_Pin *self,
                         kb_Error   (*on_high)(kb_rpi2_Pin*,
                                               kb_rpi2_Sensor*,
                                               kb_rpi2_Event*,
                                               kb_rpi2_Context*));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_high(kb_rpi2_Pin *self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_low(kb_rpi2_Pin *self,
                        kb_Error   (*on_low)(kb_rpi2_Pin*,
                                             kb_rpi2_Sensor*,
                                             kb_rpi2_Event*,
                                             kb_rpi2_Context*));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_low(kb_rpi2_Pin *self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_callback_args(kb_rpi2_Pin      *self,
                          kb_rpi2_Sensor  **sensor,
                          kb_rpi2_Event   **event,
                          kb_rpi2_Context **context);


/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t       count;
    kb_rpi2_Pin *pins;
} kb_rpi2_PinArray;

#endif /* __KB_RPI2_PINS_H_15777440527397069__ */
