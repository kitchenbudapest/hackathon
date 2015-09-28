/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN1 = 0,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
    kb_rpi2_Pin_OUTPUT,
};
/* Initial pulls */
static kb_rpi2_PinPull PIN_PULLS[] =
{
    kb_rpi2_Pin_OFF,
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_LOW,
};


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_ServoMotor_new(kb_rpi2_sensors_ServoMotor **const self,
                               kb_rpi2_Event               *const event,
                               kb_rpi2_PinId                      pin_id)
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
    kb_rpi2_sensors_ServoMotor *servo_motor;
    if (!(servo_motor = malloc(sizeof(kb_rpi2_sensors_ServoMotor))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_ServoMotor_ini(servo_motor, event, pin_id)))
    {
        free(servo_motor);
        return error;
    }

    /* If everything went fine, return values */
    *self = servo_motor;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_ServoMotor_ini(kb_rpi2_sensors_ServoMotor *const self,
                               kb_rpi2_Event              *const event,
                               kb_rpi2_PinId                     pin_id)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Initialize instance as Sensor */
    kb_Error error;
    if ((error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                    event,
                                    (size_t)1,
                                    &pin_id,
                                    PIN_ROLES,
                                    PIN_PULLS,
                                    PIN_STATES)))
        return error;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_ServoMotor_fin(kb_rpi2_sensors_ServoMotor *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_ServoMotor_del(kb_rpi2_sensors_ServoMotor **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_ServoMotor_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_ServoMotor_rotate_degree(kb_rpi2_sensors_ServoMotor *const self,
                                         double                            degree)
{
    /*
     * TODO: degrad convertwer =. http://stackoverflow.com/questions/14920675
     */
    /* Propagate error from wrapped method */
    return kb_rpi2_sensors_ServoMotor_rotate_radian(self, ...);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_ServoMotor_rotate_radian(kb_rpi2_sensors_ServoMotor *const self,
                                         double                            radian)
{
    /* If everything went fine */
    return kb_OKAY;
}
