/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/events.h> /*
    macro : kb_rpi2_PIN_COUNT
    type  : kb_rpi2_Event
*/

/*----------------------------------------------------------------------------*/
#define INITIAL_SENSORS_LIMIT (size_t)32


/*----------------------------------------------------------------------------*/
#define kb_rpi2_CHECK_SELF_IS_NULL(S)                                          \
    if (!S)                                                                    \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
#define kb_rpi2_CHECK_PIN_ID_IN_RANGE(P)                                       \
    if (P < 0 &&                                                               \
        P >= kb_rpi2_PIN_COUNT)                                                \
        return kb_INVALID_PIN_ID;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Event_new(kb_rpi2_Event   *const *self,
                  kb_rpi2_Context *const  context)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Create new Event object */
    kb_rpi2_Event *event;
    if (!(event = malloc(sizeof(kb_rpi2_Event))))
        return kb_ALLOC_FAIL;

    /* "Zero out" all Pin objects in the array */
    for (size_t i=0; i<kb_rpi2_PIN_COUNT; i++)
        event->pins[i] = NULL;

    /* Create sensor's collection */
    kb_rpi2_Sensor *sensors;
    if (!(sensors = malloc(sizeof(kb_rpi2_Sensor *)*INITIAL_SENSORS_LIMIT))
        return kb_ALLOC_FAIL;

    /* Store sensors information */
    event->sensors       = sensors;
    event->sensors_limit = INITIAL_SENSORS_LIMIT;
    event->sensors_count = 0;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_del(kb_rpi2_Event *const *self)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    size_t i;

    /* Delete all Pins objects in the array */
    for (i=0; i<kb_rpi2_PIN_COUNT; i++)
        kb_rpi2_Pin_del(self->pins[i]);

    /* Delete all Sensor objects in the array */
    for (i=0; i<(*self)->sensors_count; i++)
        kb_rpi2_Sensor_del((*self)->sensors + i);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_use_pin(kb_rpi2_Event  *self,
                      kb_rpi2_PinId   pin_id,
                      kb_rpi2_Sensor *sensor)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Check validity of `pin_id` */
    kb_rpi2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG3_IS_NULL;

    /* If `sensor` is not bound to this Event object */
    if (self->sensors[sensor->id] != sensor)
        return kb_SENSOR_IS_NOT_IN_EVENT;

    /* If this Event object is already using this Pin object */
    if (self->pins[pin_id])
        return kb_PIN_ALREADY_USED;

    /* Create new Pin object */
    return kb_rpi2_Pin_new(self->pins + pin_id, pin_id, sensor);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_drop_pin(kb_rpi2_Event *self,
                       kb_rpi2_PinId  pin_id)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Check validity of `pin_id` */
    kb_rpi2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Delete Pin object */
    kb_rpi2_Pin_del(self->pins + pin_id);

    /* Remove pin */
    self->pins[pin_id] = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_high(kb_rpi2_Event *self,
                           kb_rpi2_PinId  pin_id)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Check validity of `pin_id` */
    kb_rpi2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Set pin to HIGH */
    switch (kb_rpi2_Pin_set_high(self->pins[pin_id]))
    {
        /* If pin is not used */
        case kb_SELF_IS_NULL:
            return kb_PIN_DOES_NOT_EXIST;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_low(kb_rpi2_Event *self,
                          kb_rpi2_PinId  pin_id)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Check validity of `pin_id` */
    kb_rpi2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Set pin to LOW */
    switch (kb_rpi2_Pin_set_low(self->pins[pin_id]))
    {
        /* If pin is not used */
        case kb_SELF_IS_NULL:
            return kb_PIN_DOES_NOT_EXIST;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_bind_sensor(kb_rpi2_Event  *self,
                          kb_rpi2_Sensor *sensor)
{
    /* If `self` is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Resize collection if there is not enough space for one more sensor */
    if (self->sensors_count + 1 >= self->sensors_limit)
    {
        /* Reallocate space for sensor */
        kb_rpi2_Sensor **sensors;
        if (!(sensors = realloc(sizeof(kb_rpi2_Sensor *)*(self->sensors_limit*2)))
            return kb_ALLOC_FAIL;

        /* Store new pointer */
        self->sensors = sensors;
        /* Update limit */
        self->sensors_count *= 2;
    }

    /* Store sensor */
    self->sensors[self->sensors_count] = sensor;
    /* Set sensor id and increase sensor counter */
    sensor->id = self->sensors_count++;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_unbind_sensor(kb_rpi2_Event  *self,
                            kb_rpi2_Sensor *sensor)
{
    /* If everything went fine */
    return kb_OKAY;
}
