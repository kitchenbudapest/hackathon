/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_LED_new(kb_rpi2_sensors_LED *const *self,
                        kb_rpi2_Event       *const  event,
                        kb_rpi2_PinId               pin_id)
{
    kb_rpi2_sensors_LED *led;
    if (!(led = malloc(sizeof(kb_rpi2_sensors_LED))))
        return kb_ALLOC_FAIL;

    kb_Error error;
    if (!(error = kb_rpi2_Sensor_init((kb_rpi2_Sensor *)led,
                                event,
                                (size_t)1,
                                &pin_id)))
        return error;

    self->pin = pin_id;

    /* If everything went fine */
    return kb_OKAY;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_del(kb_rpi2_sensors_LED *const *self)
{
    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_on(kb_rpi2_sensors_LED *const self)
{
    /* Set pin HIGH */
    kb_rpi2_Event_set_pin_high(self->event, self->pin);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_off(kb_rpi2_sensors_LED *const self)
{
    /* Set pin LOW */
    kb_rpi2_Event_set_pin_low(self->event, self->pin);

    /* If everything went fine */
    return kb_OKAY;
}
