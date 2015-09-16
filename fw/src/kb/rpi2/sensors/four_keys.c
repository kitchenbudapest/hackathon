/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN_ROW = 0,
    PIN_COL1,
    PIN_COL2,
    PIN_COL3,
    PIN_COL4,
};


/*----------------------------------------------------------------------------*/
/* Callback wrapper */
#define ON_KEY_X_FUNCTION(KEY)                                                 \
    static kb_Error                                                            \
    FourKeys_on_key_##KEY(kb_rpi2_Pin     *const pin,                          \
                          kb_rpi2_Sensor  *const sensor,                       \
                          kb_rpi2_Event   *const event,                        \
                          kb_rpi2_Context *const context)                      \
    {                                                                          \
        /* If `sensor` is NULL */                                              \
        if (!sensor)                                                           \
            return kb_ARG2_IS_NULL;                                            \
        /* Call original callback */                                           \
        return ((kb_rpi2_sensor_FourKeys *const)sensor)->on_key_##KEY(sensor,  \
                                                                      event,   \
                                                                      context);\
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Callback wrappers */
ON_KEY_X_FUNCTION(1)
ON_KEY_X_FUNCTION(2)
ON_KEY_X_FUNCTION(3)
ON_KEY_X_FUNCTION(4)


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_FourKeys_new(kb_rpi2_sensors_FourKeys **const self,
                             kb_rpi2_Event             *const event,
                             kb_rpi2_PinId                    pin_row,
                             kb_rpi2_PinId                    pin_col1,
                             kb_rpi2_PinId                    pin_col2,
                             kb_rpi2_PinId                    pin_col3,
                             kb_rpi2_PinId                    pin_col4)
{

}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_ini(kb_rpi2_sensors_FourKeys *const self,
                             kb_rpi2_Event            *const event,
                             kb_rpi2_PinId                   pin_row,
                             kb_rpi2_PinId                   pin_col1,
                             kb_rpi2_PinId                   pin_col2,
                             kb_rpi2_PinId                   pin_col3,
                             kb_rpi2_PinId                   pin_col4)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Create array from arguments */
    kb_rpi2_PinId pin_ids[] =
    {
        pin_row,
        pin_col1,
        pin_col2,
        pin_col3,
        pin_col4,
    };

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                    event,
                                    (sizeof pin_ids)/sizeof(kb_rpi2_PinId),
                                    pin_ids))
        return error;

    kb_rpi2_Sensor_bind_on_pin_high();

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_fin(kb_rpi2_sensors_FourKeys *const self)
{
    (void)self;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_del(kb_rpi2_sensors_FourKeys **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_sensors_FourKeys_fin(*self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_KEY_X_BIND_FUNCTION(KEY)                                             \
    kb_Error                                                                    \
    kb_rpi2_sensors_FourKeys_bind_on_key_##KEY(kb_rpi2_sensors_FourKeys *const self, \
                                               kb_Error (*on_key_##KEY)(kb_rpi2_Sensor  *const, \
                                                                        kb_rpi2_Event   *const, \
                                                                        kb_rpi2_Context *const))\
    {
        /* If any of the arguments is NULL */                                   \
        if (!self)                                                              \
            return kb_SELF_IS_NULL;                                             \
        else if (!on_key_##KEY)                                                 \
            return kb_ARG2_IS_NULL;                                             \
                                                                                \
        /* Assign new callback */                                               \
        self->on_key_##KEY = on_key_##KEY;                                      \
        /* Set wrapper callback to Pin object */                                \
        kb_rpi2_Pin *pin;                                                       \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self, PIN_COL##KEY, &pin);\
        kb_rpi2_Pin_bind_on_high(pin, FourKeys_on_key_##KEY);                   \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
ON_KEY_X_BIND_FUNCTION(1)
ON_KEY_X_BIND_FUNCTION(2)
ON_KEY_X_BIND_FUNCTION(3)
ON_KEY_X_BIND_FUNCTION(4)



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_KEY_X_UNBIND_FUNCTION(KEY)                                           \
    kb_Error                                                                    \
    kb_rpi2_sensors_FourKeys_bind_on_key_##KEY(kb_rpi2_sensors_FourKeys *const self, \
                                               kb_Error (*on_key_##KEY)(kb_rpi2_Sensor  *const, \
                                                                        kb_rpi2_Event   *const, \
                                                                        kb_rpi2_Context *const))\
    {
        /* If any of the arguments is NULL */                                   \
        if (!self)                                                              \
            return kb_SELF_IS_NULL;                                             \
        else if (!on_key_##KEY)                                                 \
            return kb_ARG2_IS_NULL;                                             \
                                                                                \
        /* Assign new callback */                                               \
        self->on_key_##KEY = NULL;                                              \
        /* Set wrapper callback to Pin object */                                \
        kb_rpi2_Pin *pin;                                                       \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self, PIN_COL##KEY, &pin);\
        kb_rpi2_Pin_unbind_on_high(pin);                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create unbinding functions */
ON_KEY_X_UNBIND_FUNCTION(1)
ON_KEY_X_UNBIND_FUNCTION(2)
ON_KEY_X_UNBIND_FUNCTION(3)
ON_KEY_X_UNBIND_FUNCTION(4)
