/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include jemalloc headers */
#include <jemalloc/jemalloc.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

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
            kb_rpi2_Pin_HIGH
            kb_rpi2_Pin_LOW
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low */
#include <kb/rpi2/sensors/leds.h>
/*  type  : kb_rpi2_sensors_LED */


/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN1 = 0,
};
/* Role values */
static kb_rpi2_PinRole pin_roles[] =
{
    kb_rpi2_Pin_OUTPUT,
};
/* Initial states */
static kb_rpi2_PinState pin_states[] =
{
    kb_rpi2_Pin_LOW,
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
    kb_Error error;
    if ((error = kb_rpi2_sensors_LED_ini(led, event, pin_id)))
    {
        free(led);
        return error;
    }

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
    if ((error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                    event,
                                    (size_t)1,
                                    &pin_id,
                                    pin_roles,
                                    pin_states)))
        return error;

    /* Initialize data */
    self->on_on  = NULL;
    self->on_off = NULL;

    /*
     * TODO: set PIN1 to output and LOW
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_fin(kb_rpi2_sensors_LED *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_del(kb_rpi2_sensors_LED **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_LED_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

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
                                        (size_t)PIN1,
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
                                        (size_t)PIN1,
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


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_bind_on_on(kb_rpi2_sensors_LED *const self,
                               kb_Error (*on_on)(kb_rpi2_sensors_LED *const,
                                                 kb_rpi2_Event       *const,
                                                 kb_rpi2_Context     *const))
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Set callback */
    self->on_on = on_on;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_unbind_on_on(kb_rpi2_sensors_LED *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Unset callback */
    self->on_on = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_bind_on_off(kb_rpi2_sensors_LED *const self,
                                kb_Error (*on_off)(kb_rpi2_sensors_LED *const,
                                                   kb_rpi2_Event       *const,
                                                   kb_rpi2_Context     *const))
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Set callback */
    self->on_off = on_off;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_LED_unbind_on_off(kb_rpi2_sensors_LED *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Unset callback */
    self->on_off = NULL;

    /* If everything went fine */
    return kb_OKAY;
}
