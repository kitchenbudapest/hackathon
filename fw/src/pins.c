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
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ARG3_IS_NULL
            kb_ALLOC_FAIL
*/

#include <kb/RPi2/pins.h> /*
    type  : kb_rpi2_Pin_State
            kb_rpi2_Pin_Id
    const : kb_rpi2_Pin_LOW
            kb_rpi2_Pin_HIGH
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
#define kb_rpi2_CHECK_SELF_IS_NULL(S) \
    if (!S)                           \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
void
kb_rpi2_print_pin_layout(void)
{
    static const char *const kb_rpi2_PIN_LAYOUT =
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

    /* Print ASCII layout */
    puts(kb_rpi2_PIN_LAYOUT);
}


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Pin_new(kb_rpi2_Pin   **self,
                kb_rpi2_PinId   pin_id,
                kb_rpi2_Sensor *sensor)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Make `self` point to NULL */
    *self = NULL;

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG3_IS_NULL;

    /* If `pin_id` is out of range */
    if (pin_id < 0 ||
        pin_id >= kb_rpi2_PIN_COUNT)
            return kb_INVALID_PIN_ID;

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
kb_rpi2_Pin_del(kb_rpi2_Pin **self)
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
kb_rpi2_Pin_reset(kb_rpi2_Pin *self)
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
kb_rpi2_Pin_set_high(kb_rpi2_Pin *self)
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
kb_rpi2_Pin_set_low(kb_rpi2_Pin *self)
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
kb_rpi2_Pin_bind_on_high(kb_rpi2_Pin    *self,
                         kb_Error (*on_high)(kb_rpi2_Pin*,
                                             kb_rpi2_Sensor*,
                                             kb_rpi2_Event*,
                                             kb_rpi2_Context*))
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
kb_rpi2_Pin_unbind_on_high(kb_rpi2_Pin *self)
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
kb_rpi2_Pin_bind_on_low(kb_rpi2_Pin    *self,
                        kb_Error (*on_low)(kb_rpi2_Pin*,
                                           kb_rpi2_Sensor*,
                                           kb_rpi2_Event*,
                                           kb_rpi2_Context*))
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
kb_rpi2_Pin_unbind_on_low(kb_rpi2_Pin *self)
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
kb_rpi2_Pin_callback_args(kb_rpi2_Pin      *self,
                          kb_rpi2_Sensor  **sensor,
                          kb_rpi2_Event   **event,
                          kb_rpi2_Context **context)
{
    *sensor = self->sensor;
    return kb_rpi2_Event_callback_args(self->sensor, event, context);
}
