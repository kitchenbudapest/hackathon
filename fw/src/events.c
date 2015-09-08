/* INFO **
** INFO */


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_Context *context;
    kb_rpi2_Pin     *pins[kb_rpi2_PIN_COUNT];
    size_t           sensor_count;
    kb_rpi2_Sensor  *sensors;
} kb_rpi2_Event;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_new(kb_rpi2_Event   **self,
                  kb_rpi2_Context  *context)
{
    kb_rpi2_Event *event;

    /* "Zero out" all pins in the array */
    for (size_t i=0; i<kb_rpi2_PIN_COUNT; i++)
        event->pins[i] = NULL;

    /* If everything went fine */
    return kb_OKAY;
}







/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_use_pin(kb_rpi2_Event *self,
                      kb_rpi2_PinId  pin_id)
{
    if (self->pins[pin_id])
        return kb_PIN_ALREADY_USED;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_high(kb_rpi2_Event *self,
                           kb_rpi2_PinId  pin_id)
{
    /* Set pin to HIGH */
    kb_rpi2_Pin_set_high(self->pins[pin_id]);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_low(kb_rpi2_Event *self,
                           kb_rpi2_PinId  pin_id)
{
    /* Set pin to LOW */
    kb_rpi2_Pin_set_low(self->pins[pin_id]);

    /* If everything went fine */
    return kb_OKAY;
}
