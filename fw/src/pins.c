/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
void
kb_RPi2_print_pin_layout(void)
{
    static const char *const kb_RPi2_PIN_LAYOUT =
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
    puts(kb_RPi2_PIN_LAYOUT);
}


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_RPi2_OKAY,
    kb_RPi2_FAIL,

    kb_RPi2_SELF_IS_NULL,
    kb_RPi2_ARG1_IS_NULL,
    kb_RPi2_ARG2_IS_NULL,
    kb_RPi2_ARG3_IS_NULL,
    kb_RPi2_ARG4_IS_NULL,
    kb_RPi2_ARG5_IS_NULL,

} kb_RPi2_Error;


#define kb_RPi2_CHECK_SELF_IS_NULL(S) \
    if (!S)                           \
        return kb_RPi2_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_RPi2_Pin_01,
    kb_RPi2_Pin_02,
    kb_RPi2_Pin_03,
} kb_RPi2_Pin_Id;


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_RPi2_Pin_LOW  = 0,
    kb_RPi2_Pin_HIGH = 1,
} kb_RPi2_Pin_State;



/*----------------------------------------------------------------------------*/
typedef struct
{
    /* Static data */
    kb_RPi2_Pin_Id    pin_id;
    kb_RPi2_Sensor    sensor;
    kb_RPi2_Pin_State state;

    /* Available callbacks */
    kb_RPi2_Error   (*on_high)(kb_RPi2_Pin*,
                               kb_RPi2_Sensor*,
                               kb_RPi2_Event*,
                               kb_RPi2_Context*);
    kb_RPi2_Error   (*on_low)(kb_RPi2_Pin*,
                              kb_RPi2_Sensor*,
                              kb_RPi2_Event*,
                              kb_RPi2_Context*);
} kb_RPi2_Pin;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_new(kb_RPi2_Pin    **self,
                kb_RPi2_Pin_Id   pin_id,
                kb_RPi2_Sensor  *sensor)
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    kb_RPi2_Pin *pin;

    ...

    pin->pin_id  = pin_id;
    pin->sensor  = sensor;
    pin->on_high = NULL;
    pin->on_low  = NULL;

    *self = pin;

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_del(kb_RPi2_Pin **self)
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_reset(kb_RPi2_Pin *self)
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_set_high(kb_RPi2_Pin *self)
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If a callback set to this pin */
    if (self->on_high)
    {
        /* Get `event` and `context` objects */
        kb_RPi2_Event   *event;
        kb_RPi2_Context *context;
        kb_RPi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_high(self,
                      self->sensor,
                      event,
                      context);
    }

    /* SWitch state */
    self->state = kb_RPi2_Pin_HIGH;

    /*
     * TODO: Set this pin HIGH via bcm2835
     */

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_set_low(kb_RPi2_Pin *self)
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If a callback set to this pin */
    if (self->on_low)
    {
        /* Get `event` and `context` objects */
        kb_RPi2_Event   *event;
        kb_RPi2_Context *context;
        kb_RPi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_low(self,
                     self->sensor,
                     event,
                     context);
    }

    /* SWitch state */
    self->state = kb_RPi2_Pin_LOW;

    /*
     * TODO: Set this pin LOW via bcm2835
     */

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_bind_on_high(kb_RPi2_Pin    *self,
                         kb_RPi2_Error (*on_high)(kb_RPi2_Pin*,
                                                  kb_RPi2_Sensor*,
                                                  kb_RPi2_Event*,
                                                  kb_RPi2_Context*))
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_unbind_on_high(kb_RPi2_Pin    *self,
                           kb_RPi2_Error (*on_high)(kb_RPi2_Pin*,
                                                    kb_RPi2_Sensor*,
                                                    kb_RPi2_Event*,
                                                    kb_RPi2_Context*))
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_bind_on_low(kb_RPi2_Pin    *self,
                        kb_RPi2_Error (*on_low)(kb_RPi2_Pin*,
                                                kb_RPi2_Sensor*,
                                                kb_RPi2_Event*,
                                                kb_RPi2_Context*))
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_RPi2_Error
kb_RPi2_Pin_unbind_on_low(kb_RPi2_Pin    *self,
                          kb_RPi2_Error (*on_low)(kb_RPi2_Pin*,
                                                  kb_RPi2_Sensor*,
                                                  kb_RPi2_Event*,
                                                  kb_RPi2_Context*))
{
    /* If self is NULL */
    kb_RPi2_CHECK_SELF_IS_NULL(self);

    /* If everything went fine */
    return kb_RPi2_OKAY;
}
