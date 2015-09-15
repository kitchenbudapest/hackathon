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
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Event
            kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Sensor_new(kb_rpi2_Sensor **const self,
                   kb_rpi2_Event  *const event,
                   size_t         *const pin_id_count,
                   kb_rpi2_PinId  *const pin_ids)
{
    (void)self;
    (void)event;
    (void)pin_id_count;
    (void)pin_ids;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    // kb_rpi2_Sensor_ini(sensor, event, pin_id_count, pin_ids);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_ini(kb_rpi2_Sensor *const self,
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
kb_rpi2_Sensor_fin(kb_rpi2_Sensor *const self)
{
    (void)self;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_del(kb_rpi2_Sensor **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

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


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_enable(kb_rpi2_Sensor *const self)
{
    (void)self;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_disable(kb_rpi2_Sensor *const self)
{
    (void)self;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_bind_pin(kb_rpi2_Sensor *const self,
                        kb_rpi2_Pin    *const pin)
{
    (void)self;
    (void)pin;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_unbind_pin(kb_rpi2_Sensor *const self,
                          kb_rpi2_Pin    *const pin)
{
    (void)self;
    (void)pin;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_bind_on_pin_high(kb_rpi2_Sensor *const self,
                                kb_rpi2_Pin    *const pin,
                                kb_Error      (*on_high)(kb_rpi2_Pin     *const,
                                                         kb_rpi2_Sensor  *const,
                                                         kb_rpi2_Event   *const,
                                                         kb_rpi2_Context *const))
{
    (void)self;
    (void)pin;

    /* If everything went fine */
    return kb_OKAY;
}
