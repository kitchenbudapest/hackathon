/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include unix headers */
#if __STDC_VERSION__ >= 199901L
    #define __USE_POSIX199309
#endif /* __STDC_VERSION__ */
#include <time.h>
/*  const : CLOCK_REALTIME
    type  : struct timespec
    func  : nanosleep
            clock_gettime */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include jemalloc headers */
#include <jemalloc/jemalloc.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ALLOC_FAIL */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Sensor_ini
            kb_rpi2_Sensor_fin
            kb_rpi2_Sensor_get_pin */
#include <kb/rpi2/pins.h>
/*  const : kb_rpi2_Pin_OUTPUT
            kb_rpi2_Pin_INPUT
            kb_rpi2_Pin_UNSET
            kb_rpi2_Pin_LOW
            kb_rpi2_Pin_OFF
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low
            kb_rpi2_Pin_listen
            kb_rpi2_Pin_is_high
            kb_rpi2_Pin_is_low */
#include <kb/rpi2/sensors/ultrasonic_sensors.h>
/*  type  : kb_rpi2_sensors_UltrasonicSensor */


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
/* Trigger signaling delay */
static const struct timespec TRIGGER_BREAK =
{
    (time_t)0,
    10000L, /* I microseconds */
};


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_new(
    kb_rpi2_sensors_UltrasonicSensor **const self,
    kb_rpi2_Event                     *const event,
    kb_rpi2_PinId                            pin_echo,
    kb_rpi2_PinId                            pin_trigger)
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
    kb_rpi2_sensors_UltrasonicSensor *ultrasonic_sensor;
    if (!(ultrasonic_sensor = malloc(sizeof(kb_rpi2_sensors_UltrasonicSensor))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_UltrasonicSensor_ini(ultrasonic_sensor,
                                                      event,
                                                      pin_echo,
                                                      pin_trigger)))
    {
        free(ultrasonic_sensor);
        return error;
    }

    /* If everything went fine, return values */
    *self = ultrasonic_sensor;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_ini(
    kb_rpi2_sensors_UltrasonicSensor *const self,
    kb_rpi2_Event                    *const event,
    kb_rpi2_PinId                           pin_echo,
    kb_rpi2_PinId                           pin_trigger)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Create array from arguments */
    kb_rpi2_PinId pin_ids[] =
    {
        pin_echo,
        pin_trigger,
    };

    /* Initialize instance as Sensor */
    kb_Error error;
    if ((error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                    event,
                                    (sizeof pin_ids)/sizeof(kb_rpi2_PinId),
                                    pin_ids,
                                    PIN_ROLES,
                                    PIN_PULLS,
                                    PIN_STATES)))
        return error;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_fin(
    kb_rpi2_sensors_UltrasonicSensor *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_del(
    kb_rpi2_sensors_UltrasonicSensor **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_UltrasonicSensor_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_UltrasonicSensor_measure(
    kb_rpi2_sensors_UltrasonicSensor *const  self,
    double                                  *distance)
{
    /* Convert to milisecond and then to milimeter */
    static const double SEC_TO_MILIMETER     = 17000000000.0;
    static const double NANOSEC_TO_MILIMETER = 0.00017;

    bool            state;
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
    *distance = ((double)(stop.tv_sec  - start.tv_sec))/SEC_TO_MILIMETER +
                ((double)(stop.tv_nsec - start.tv_nsec))*NANOSEC_TO_MILIMETER;

    /* If everything went fine */
    return kb_OKAY;
}
