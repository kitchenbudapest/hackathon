/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY */
#include <kb/types.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Event
            kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Sensor_new(kb_rpi2_Sensor **const self)
{
    (void)self;

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
    (void)self;
    (void)event;
    (void)pin_id_count;
    (void)pin_ids;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_del(kb_rpi2_Sensor **const self)
{
    (void)self;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_callback_args(kb_rpi2_Sensor   *const self,
                             kb_rpi2_Event   **const event,
                             kb_rpi2_Context **const context)
{
    (void)self;
    (void)event;
    (void)context;

    /* If everything went fine */
    return kb_OKAY;

    /* Set event and get context */
    // *event = self->event;
    // return kb_rpi2_Event_callback_args(self->event, context);
}
