/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include unix headers */
#if __STDC_VERSION__ >= 199901L
    #define __USE_POSIX199309
#endif /* __STDC_VERSION__ */
#include <time.h>
/*  type  : struct timespec
    func  : nanosleep
            clock_gettime */

/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN_ECHO = 0,
    PIN_TRIGGER,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_OUTPUT,
};
/* Initial pulls */
static kb_rpi2_PinPull PIN_PULLS[] =
{
    kb_rpi2_Pin_OFF,
    kb_rpi2_Pin_OFF,
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_UNSET,
    kb_rpi2_Pin_LOW,
};
/* Trigger break */
static const struct timespec TRIGGER_BREAK =
{
    (time_t)0,
    10000L, /* I microseconds */
};


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_measure(
    kb_rpi2_sensors_UltrasonicSensor *const  self,
    double                                  *distance)
{
    /* Convert to milisecond and then to milimeter */
    static const double SEC_TO_MILIMETER     = 17000000000.0;
    static const double NANOSEC_TO_MILIMETER = 17.0;

    bool            state;
    double          result;
    kb_Error        error;
    struct timespec start,
                    stop;

    /* Get pins */
    kb_rpi2_Pin *pin_echo,
                *pin_trigger;
    if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                        PIN_ECHO,
                                        &pin_echo)))
        return error;
    if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                        PIN_TRIGGER,
                                        &pin_trigger)))
        return error;

    /* Trigger sensor */
    kb_rpi2_Pin_set_high(pin_trigger);
    nanosleep(&TRIGGER_BREAK, NULL);
    kb_rpi2_Pin_set_low(pin_trigger);

    /* Detect start point of measurement */
    do
    {
        kb_rpi2_Pin_listen(pin_echo);
        kb_rpi2_Pin_is_low(pin_echo, &state);
    }
    while (state);
    /* Start measuring */
    clock_gettime(CLOCK_REALTIME, &start);

    /* Detect end point of measurement */
    do
    {
        kb_rpi2_Pin_listen(pin_echo);
        kb_rpi2_Pin_is_high(pin_echo, &state);
    }
    while (state);
    /* Stop measuring */
    clock_gettime(CLOCK_REALTIME, &stop);

    /* Calculate distance based on the ellapsed time */
    *distance = ((double)(stop.tv_sec  - start.tv_sec))*SEC_TO_MILIMETER +
                ((double)(stop.tv_nsec - start.tv_nsec))*NANOSEC_TO_MILIMETER;

    /* If everything went fine */
    return kb_OKAY;
}
