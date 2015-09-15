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
/*  type  : kb_rpi2_PinState
            kb_rpi2_PinId
    const : kb_rpi2_Pin_LOW
            kb_rpi2_Pin_HIGH */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
const char *const kb_rpi2_PIN_LAYOUT =
    "           +-----+-----+\n"
    "         0 |     |     |  1\n"
    "           +-----+-----+\n"
    "         2 |     |     |  3\n"
    "           +-----+-----+\n"
    "         4 |     |     |  5\n"
    "+---+------+-----+-----+\n"
    "| G |    6 |     |     |  7\n"
    "| P |      +-----+-----+\n"
    "| I |    8 |     |     |  9\n"
    "| O |      +-----+-----+\n"
    "+---+   10 |     |     | 11\n"
    "           +-----+-----+\n"
    "        12 |     |     | 13\n"
    "           +-----+-----+\n"
    "        14 |     |     | 15\n"
    "           +-----+-----+\n"
    "        16 |     |     | 17\n"
    "           +-----+-----+\n"
    "        18 |     |     | 19\n"
    "           +-----+-----+\n"
    "        20 |     |     | 21\n"
    "           +-----+-----+\n"
    "        22 |     |     | 23\n"
    "           +-----+-----+\n"
    "        24 |     |     | 25\n"
    "           +-----+-----+\n"
    "        26 |     |     | 27\n"
    "           +-----+-----+\n"
    "        28 |     |     | 29\n"
    "           +-----+-----+\n"
    "        30 |     |     | 31\n"
    "           +-----+-----+\n"
    "        32 |     |     | 33\n"
    "           +-----+-----+\n"
    "        34 |     |     | 35\n"
    "           +-----+-----+\n"
    "        36 |     |     | 37\n"
    "           +-----+-----+\n"
    "        38 |     |     | 39\n"
    "           +-----+-----+\n";


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
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Create new Pin object */
    kb_rpi2_Pin *pin;
    if (!(pin = malloc(sizeof(kb_rpi2_Pin))))
        return kb_ALLOC_FAIL;

    /* Initialize new Pin object */
    kb_rpi2_Pin_ini(pin, pin_id, sensor);

    /* If everything went fine, return values */
    *self = pin;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_ini(kb_rpi2_Pin    *const self,
                kb_rpi2_PinId         pin_id,
                kb_rpi2_Sensor *const sensor)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Initialize Pin object */
    self->id      = pin_id;

    /*
     * TODO: Get initial state from bcm2835 (somehow..)
     */

    self->state   = kb_rpi2_Pin_LOW;
    self->sensor  = sensor;
    self->on_high = NULL;
    self->on_low  = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_fin(kb_rpi2_Pin *const self)
{
    if (!self)
        return kb_SELF_IS_NULL;

    /* Unbind pin from sensor */
    kb_rpi2_Sensor_unbind_pin(self->sensor, self);

    /*
     * TODO: Reset this pin via bcm2835
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_del(kb_rpi2_Pin **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_Pin_fin(*self);

    /* Deallocate instance and redirect self */
    free(*self);
    *self = NULL;

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
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!sensor)
        return kb_ARG2_IS_NULL;

    /* Set callback arguments */
    *sensor = self->sensor;
    switch (kb_rpi2_Sensor_callback_args(self->sensor, event, context))
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


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_reset(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

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
    if (!self)
        return kb_SELF_IS_NULL;

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
    if (!self)
        return kb_SELF_IS_NULL;

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
    if (!self)
        return kb_SELF_IS_NULL;

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
    if (!self)
        return kb_SELF_IS_NULL;

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
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Unset callback function */
    self->on_low = NULL;

    /* If everything went fine */
    return kb_OKAY;
}
