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
#define kb_rpi2_CHECK_SELF_IS_NULL(S) \
    if (!S)                           \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Sensor_new(kb_rpi2_Sensor *const *self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_init(kb_rpi2_Sensor *const self,
                    kb_rpi2_Event  *const event,
                    size_t         *const pin_id_count,
                    kb_rpi2_PinId  *const pin_ids)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    self->event = event;
    kb_Error error;
    error = kb_rpi2_PinArray(pin_id_count, pin_ids);
    if (!)

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_del(kb_rpi2_Sensor *const *self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_callback_args(kb_rpi2_Sensor  *const  self,
                             kb_rpi2_Event   *const *event,
                             kb_rpi2_Context *const *context)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Set event and get context */
    *event = self->event;
    return kb_rpi2_Event_callback_args(self->event, context);
}
