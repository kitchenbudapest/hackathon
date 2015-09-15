/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN1 = 0,
};


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_LED_new(kb_rpi2_sensors_LED **const self,
                        kb_rpi2_Event        *const event,
                        kb_rpi2_PinId               pin_id)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `event` is NULL */
    if (!event)
        return kb_ARG2_IS_NULL;

    /* Allocate space for new instance */
    kb_rpi2_sensors_LED *led;
    if (!(led = malloc(sizeof(kb_rpi2_sensors_LED))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_rpi2_sensors_LED_ini(led, event, pin_id);

    /* If everything went fine, return values */
    *self = led;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_ini(kb_rpi2_sensors_LED *const self,
                        kb_rpi2_Event       *const event,
                        kb_rpi2_PinId              pin_id)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Initialize instance as Sensor */
    kb_Error error;
    if (error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                   event,
                                   (size_t)1,
                                   &pin_id))
        return error;

    /* Initialize data */
    self->on_on  = NULL;
    self->on_off = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_fin(kb_rpi2_sensors_LED *const self)
{
    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_del(kb_rpi2_sensors_LED **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_on(kb_rpi2_sensors_LED *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Get pin */
    kb_rpi2_Pin *pin;
    kb_Error     error;
    if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                        PIN1,
                                        &pin)))
        return error;

    /* Set pin HIGH */
    kb_rpi2_Pin_set_high(pin);

    /* If there is an `on_on` callback, call it */
    if (self->on_on)
    {
        /* Get callback arguments */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args((kb_rpi2_Sensor *const)self,
                                     &event,
                                     &context);

        /* Call callback */
        self->on_on(self, event, context);
    }

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_off(kb_rpi2_sensors_LED *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Get pin */
    kb_rpi2_Pin *pin;
    kb_Error     error;
    if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                        PIN1,
                                        &pin)))
        return error;

    /* Set pin LOW */
    kb_rpi2_Pin_set_low(pin);

    /* If there is an `on_on` callback, call it */
    if (self->on_off)
    {
        /* Get callback arguments */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args((kb_rpi2_Sensor *const)self,
                                     &event,
                                     &context);

        /* Call callback */
        self->on_off(self, event, context);
    }

    /* If everything went fine */
    return kb_OKAY;
}
