/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */
#include <math.h>
/*  const : M_PI
    func  : fmod
            fabs
            floor */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include unix headers */
#if __STDC_VERSION__ >= 199901L
    #define __USE_POSIX199309
#endif /* __STDC_VERSION__ */
#include <time.h>
/*  type  : struct timespec
    func  : nanosleep */

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
            kb_rpi2_Pin_LOW
            kb_rpi2_Pin_OFF
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low */
#include <kb/rpi2/sensors/step_motors.h>
/*  type  : kb_rpi2_sensors_StepMotor */

/* If M_PI is not defined (as it is not part of the standard) */
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN_IN1 = 0,
    PIN_IN2,
    PIN_IN3,
    PIN_IN4,
    PINS_COUNT,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
    kb_rpi2_Pin_OUTPUT,
    kb_rpi2_Pin_OUTPUT,
    kb_rpi2_Pin_OUTPUT,
    kb_rpi2_Pin_OUTPUT,
};
/* Initial pulls */
static kb_rpi2_PinPull PIN_PULLS[] =
{
    kb_rpi2_Pin_OFF,
    kb_rpi2_Pin_OFF,
    kb_rpi2_Pin_OFF,
    kb_rpi2_Pin_OFF,
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_LOW,
};
/* 360 degree in radian */
static const double PI2 = M_PI*2.0;
/* Half stepping */
static const int SEQUENCE[][4] =
{
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
};
/* Full cycle */
static const double CYCLE = 512.0;
/* Pause after each polar-change */
static const struct timespec BREAK =
{
    (time_t)0,
    1000000L,
};
/* Double boundary */
static const double ZERO = 0.0001; /* 1/512 = 0.001953125 */


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_StepMotor_new(kb_rpi2_sensors_StepMotor **const self,
                              kb_rpi2_Event              *const event,
                              kb_rpi2_PinId                     pin_in1,
                              kb_rpi2_PinId                     pin_in2,
                              kb_rpi2_PinId                     pin_in3,
                              kb_rpi2_PinId                     pin_in4)
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
    kb_rpi2_sensors_StepMotor *step_motor;
    if (!(step_motor = malloc(sizeof(kb_rpi2_sensors_StepMotor))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_StepMotor_ini(step_motor,
                                               event,
                                               pin_in1,
                                               pin_in2,
                                               pin_in3,
                                               pin_in4)))
    {
        free(step_motor);
        return error;
    }

    /* If everything went fine, return values */
    *self = step_motor;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_ini(kb_rpi2_sensors_StepMotor *const self,
                              kb_rpi2_Event             *const event,
                              kb_rpi2_PinId                    pin_in1,
                              kb_rpi2_PinId                    pin_in2,
                              kb_rpi2_PinId                    pin_in3,
                              kb_rpi2_PinId                    pin_in4)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Create array from arguments */
    kb_rpi2_PinId pin_ids[] =
    {
        pin_in1,
        pin_in2,
        pin_in3,
        pin_in4,
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
kb_rpi2_sensors_StepMotor_fin(kb_rpi2_sensors_StepMotor *const self)
{
    /* Set all pins to LOW */
    kb_Error error;
    kb_rpi2_Pin *pin;
    for (int i=0; i<PINS_COUNT; i++)
    {
        if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                            i,
                                            &pin)))
            return error;
        kb_rpi2_Pin_set_low(pin);
    }

    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_del(kb_rpi2_sensors_StepMotor **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_StepMotor_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate(kb_rpi2_sensors_StepMotor *const self,
                                 double                           rotation)
{
    /* Counter variables */
    size_t i,
           j,
           k;

    /* Get pins */
    kb_Error     error;
    kb_rpi2_Pin *pins[PINS_COUNT];
    for (i=0; i<(size_t)PINS_COUNT; i++)
        if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                                            i,
                                            pins + i)))
            return error;

    if (rotation > ZERO)
    {
        /* Do the cycles */
        for (i=0; i<(size_t)floor(CYCLE*rotation); i++)
            for (j=0; j<((sizeof SEQUENCE)/(sizeof SEQUENCE[0])); j++)
            {
                /* Set pins */
                for (k=0; k<((sizeof SEQUENCE[0])/sizeof(int)); k++)
                    if (SEQUENCE[j][k])
                        kb_rpi2_Pin_set_high(pins[k]);
                    else
                        kb_rpi2_Pin_set_low(pins[k]);
                /* Give time for the magnets to take effect */
                nanosleep(&BREAK, NULL);
            }
    }
    else if (rotation < -ZERO)
    {
        /* Do the cycles */
        for (i=0; i<(size_t)floor(fabs(CYCLE*rotation)); i++)
            for (j=((sizeof SEQUENCE)/(sizeof SEQUENCE[0]))-(size_t)1;
                 j<((sizeof SEQUENCE)/(sizeof SEQUENCE[0])); j--)
            {
                /* Set pins */
                for (k=0; k<((sizeof SEQUENCE[0])/sizeof(int)); k++)
                    if (SEQUENCE[j][k])
                        kb_rpi2_Pin_set_high(pins[k]);
                    else
                        kb_rpi2_Pin_set_low(pins[k]);
                /* Give time for the magnets to take effect */
                nanosleep(&BREAK, NULL);
            }
    }


    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate_degree(kb_rpi2_sensors_StepMotor *const self,
                                        double                           degree)
{
    /* Propagate error from wrapped method */
    return kb_rpi2_sensors_StepMotor_rotate(self, fmod(degree, 360.0)/360.0);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate_radian(kb_rpi2_sensors_StepMotor *const self,
                                        double                           radian)
{
    /* Propagate error from wrapped method */
    return kb_rpi2_sensors_StepMotor_rotate(self, fmod(radian, PI2)/PI2);
}
