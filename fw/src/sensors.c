/* INFO **
** INFO */

/* Include standard headers */
#include <stdlib.h> /*
    func  : malloc
            free
*/


/* Include kibu headers */
#include <kb/errors.h> /*
    type  : kb_Error
    const : kb_OKAY
*/


/*----------------------------------------------------------------------------*/
#define kb_RPi2_CHECK_SELF_IS_NULL(S) \
    if (!S)                           \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
kb_Error
kb_RPi2_Sensor_new(kb_RPi2_Sensor **self)
{
    /* If `self` is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_RPi2_Sensor_init(kb_RPi2_Sensor *self,
                    kb_RPi2_Event  *event,
                    size_t         *pin_id_count,
                    kb_RPi2_PinId  *pin_ids)
{
    /* If `self` is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    self->event = event;
    kb_Error error;
    error = kb_RPi2_PinArray(pin_id_count, pin_ids);
    if (!)

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_RPi2_Sensor_del(kb_RPi2_Sensor **self)
{
    /* If `self` is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_RPi2_Sensor_callback_args(kb_RPi2_Sensor   *self,
                             kb_RPi2_Event   **event,
                             kb_RPi2_Context **context)
{
    /* If `self` is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* Set event and get context */
    *event = self->event;
    return kb_RPi2_Event_callback_args(self->event, context);
}
