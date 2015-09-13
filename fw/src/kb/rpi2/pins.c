/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ARG3_IS_NULL
            kb_ALLOC_FAIL */
#include <kb/rpi2/pins.h>
/*  type  : kb_rpi2_Pin_State
            kb_rpi2_Pin_Id
    const : kb_rpi2_Pin_LOW
            kb_rpi2_Pin_HIGH */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
#define kb_rpi2_CHECK_SELF_IS_NULL(S)                                          \
    if (!S)                                                                    \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG3_IS_NULL:
        if sensor argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of the new Pin object failed */

kb_Error
kb_rpi2_Pin_new(kb_rpi2_Pin    **const self,
                kb_rpi2_PinId          pin_id,
                kb_rpi2_Sensor  *const sensor)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Make `self` point to NULL */
    *self = NULL;

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Create new Pin object */
    kb_rpi2_Pin *pin;
    if (!(pin = malloc(sizeof(kb_rpi2_Pin))))
        return kb_ALLOC_FAIL;

    /* Initialize Pin object */
    pin->id      = pin_id;

    /*
     * TODO: Get initial state from bcm2835 (somehow..)
     */

    pin->state   = kb_rpi2_Pin_LOW;

    pin->sensor  = sensor;
    pin->on_high = NULL;
    pin->on_low  = NULL;

    /* Make `self` point to the new Pin object */
    *self = pin;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_del(kb_rpi2_Pin *const *self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Unbind pin from sensor */
    kb_rpi2_Sensor_unbind_pin((*self)->sensor);

    /*
     * TODO: Reset this pin via bcm2835
     */

    /* Deallocate Pin object */
    free(*self);

    /* Make `self` point to NULL */
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_reset(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /*
     * TODO: Reset this pin via bcm2835
     *       Reset self->state as well
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_high(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If a callback set to this pin */
    if (self->on_high)
    {
        /* Get `event` and `context` objects */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_high(self,
                      self->sensor,
                      event,
                      context);
    }

    /* SWitch state */
    self->state = kb_rpi2_Pin_HIGH;

    /*
     * TODO: Set this pin HIGH via bcm2835
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_low(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If a callback set to this pin */
    if (self->on_low)
    {
        /* Get `event` and `context` objects */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_low(self,
                     self->sensor,
                     event,
                     context);
    }

    /* Switch state */
    self->state = kb_rpi2_Pin_LOW;

    /*
     * TODO: Set this pin LOW via bcm2835
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_high(kb_rpi2_Pin  *const self,
                         kb_Error    (*on_high)(kb_rpi2_Pin     *const,
                                                kb_rpi2_Sensor  *const,
                                                kb_rpi2_Event   *const,
                                                kb_rpi2_Context *const))
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If `on_high` is NULL */
    if (!on_high)
        return kb_ARG2_IS_NULL;

    /* Set callback function */
    self->on_high = on_high;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_high(kb_rpi2_Pin *const self)
{
    /* If self is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Unset callback function */
    self->on_high = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_low(kb_rpi2_Pin  *const self,
                        kb_Error    (*on_low)(kb_rpi2_Pin     *const,
                                              kb_rpi2_Sensor  *const,
                                              kb_rpi2_Event   *const,
                                              kb_rpi2_Context *const))
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If `on_low` is NULL */
    if (!on_low)
        return kb_ARG2_IS_NULL;

    /* Set callback function */
    self->on_low = on_low;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_low(kb_rpi2_Pin *const self)
{
    /* If self is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Unset callback function */
    self->on_low = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_callback_args(kb_rpi2_Pin      *const self,
                          kb_rpi2_Sensor  **const sensor,
                          kb_rpi2_Event   **const event,
                          kb_rpi2_Context **const context)
{
    /* If self is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG2_IS_NULL;

    /* Set callback arguments */
    *sensor = self->sensor;
    switch (kb_rpi2_Event_callback_args(self->sensor, event, context))
    {
        /* If `event` is NULL */
        case kb_ARG2_IS_NULL:
            return kb_ARG3_IS_NULL;

        /* If `context` is NULL */
        case kb_ARG3_IS_NULL:
            return kb_ARG4_IS_NULL;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}
