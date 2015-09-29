/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

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
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Event
            kb_rpi2_Context */
#include <kb/rpi2/pins.h>
/*  const : kb_rpi2_Pin_INPUT
            kb_rpi2_Pin_UP
            kb_rpi2_Pin_UNSET
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_bind_on_high
            kb_rpi2_Pin_unbind_on_high */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Sensor_ini
            kb_rpi2_Sensor_fin
            kb_rpi2_Sensor_get_pin */
#include <kb/rpi2/sensors/rotary_encoders.h>
/*  type  : kb_rpi2_sensors_RotaryEncoder */


/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN_SWITCH = 0,
    PIN_DATA,
    PIN_CLOCK,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_INPUT,
};
/* Initial pulls */
static kb_rpi2_PinPull PIN_PULLS[] =
{
    kb_rpi2_Pin_UP,
    kb_rpi2_Pin_UP,
    kb_rpi2_Pin_UP,
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_UNSET,
    kb_rpi2_Pin_UNSET,
    kb_rpi2_Pin_UNSET,
};


/*----------------------------------------------------------------------------*/
/* Callback wrappers */
static kb_Error
RotaryEncoder_on_click(kb_rpi2_Pin     *const pin,
                       kb_rpi2_Sensor  *const sensor,
                       kb_rpi2_Event   *const event,
                       kb_rpi2_Context *const context)
{
    (void)pin;
    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG2_IS_NULL;
    /* Call original callback */
    return ((kb_rpi2_sensors_RotaryEncoder *const)sensor)->on_click(
        (kb_rpi2_sensors_RotaryEncoder *const)sensor,
        event,
        context);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static kb_Error
RotaryEncoder_on_rotate(kb_rpi2_Pin     *const pin_clock,
                        kb_rpi2_Sensor  *const sensor,
                        kb_rpi2_Event   *const event,
                        kb_rpi2_Context *const context)
{
    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG2_IS_NULL;

    kb_Error error;
    kb_rpi2_Pin *pin_data;
    if ((error = kb_rpi2_Sensor_get_pin(sensor, PIN_DATA, &pin_data)))
        return error;

    /* Read pin state */
    kb_rpi2_Pin_listen(pin_data);

    /* If the knob is rotating and it is clock wise */
    error = kb_OKAY;
    if (pin_clock->state == pin_data->state)
    {
        /* If there is a callback for counter clock wise rotation */
        if (((kb_rpi2_sensors_RotaryEncoder *const)sensor)->on_rotate_counter_clock_wise)
            error =
                ((kb_rpi2_sensors_RotaryEncoder *const)sensor)->on_rotate_counter_clock_wise(
                    (kb_rpi2_sensors_RotaryEncoder *const)sensor,
                    event,
                    context);
    }
    /* If the knob is rotating and it is counter clock wise */
    else
    {
        /* If there is a callback for clock wise rotation */
        if (((kb_rpi2_sensors_RotaryEncoder *const)sensor)->on_rotate_clock_wise)
            error =
                ((kb_rpi2_sensors_RotaryEncoder *const)sensor)->on_rotate_clock_wise(
                    (kb_rpi2_sensors_RotaryEncoder *const)sensor,
                    event,
                    context);
    }

    /* Update stored value */
    ((kb_rpi2_sensors_RotaryEncoder *const)sensor)->prev_state = pin_clock->state;

    /* Propagate return signal */
    return error;
}


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_RotaryEncoder_new(kb_rpi2_sensors_RotaryEncoder **const self,
                                  kb_rpi2_Event                  *const event,
                                  kb_rpi2_PinId                         pin_switch,
                                  kb_rpi2_PinId                         pin_data,
                                  kb_rpi2_PinId                         pin_clock)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `event` is NULL */
    if (!event)
        return kb_ARG2_IS_NULL;

    /* Create new instance */
    kb_rpi2_sensors_RotaryEncoder *rotary_encoder;
    if (!(rotary_encoder = malloc(sizeof(kb_rpi2_sensors_RotaryEncoder))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_RotaryEncoder_ini(rotary_encoder,
                                                   event,
                                                   pin_switch,
                                                   pin_data,
                                                   pin_clock)))
    {
        free(rotary_encoder);
        return error;
    }

    /* If everything went fine, return values */
    *self = rotary_encoder;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_ini(kb_rpi2_sensors_RotaryEncoder *const self,
                                  kb_rpi2_Event                 *const event,
                                  kb_rpi2_PinId                        pin_switch,
                                  kb_rpi2_PinId                        pin_data,
                                  kb_rpi2_PinId                        pin_clock)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Create array from arguments */
    kb_rpi2_PinId pin_ids[] =
    {
        pin_switch,
        pin_data,
        pin_clock,
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

    /* Set static values */
    self->on_click                     = NULL;
    self->on_rotate_clock_wise         = NULL;
    self->on_rotate_counter_clock_wise = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_fin(kb_rpi2_sensors_RotaryEncoder *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_del(kb_rpi2_sensors_RotaryEncoder **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_RotaryEncoder_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_click(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_click)(kb_rpi2_sensors_RotaryEncoder *const,
                         kb_rpi2_Event                 *const,
                         kb_rpi2_Context               *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_click)
        return kb_ARG2_IS_NULL;

    /* Assign new callback */
    self->on_click = on_click;
    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_switch;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                           PIN_SWITCH,
                           &pin_switch);

    /* Set wrapper callback to pin */
    kb_rpi2_Pin_bind_on_low(pin_switch, RotaryEncoder_on_click);

    /* If everything went fine */
    return kb_OKAY;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_click(
    kb_rpi2_sensors_RotaryEncoder *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Assign new callback */
    self->on_click = NULL;
    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_switch;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                           PIN_SWITCH,
                           &pin_switch);

    /* Unset wrapper callback of pin */
    kb_rpi2_Pin_unbind_on_low(pin_switch);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_rotate_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_rotate_clock_wise)(kb_rpi2_sensors_RotaryEncoder *const,
                                     kb_rpi2_Event                 *const,
                                     kb_rpi2_Context               *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_rotate_clock_wise)
        return kb_ARG2_IS_NULL;

    /* Assign new callback */
    self->on_rotate_clock_wise = on_rotate_clock_wise;

    /* If pins' callbacks already set by the other direction */
    if (self->on_rotate_counter_clock_wise)
        return kb_OKAY;

    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_clock;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                            PIN_CLOCK,
                            &pin_clock);

    /* Set wrapper callback to pin */
    kb_rpi2_Pin_bind_on_low(pin_clock, RotaryEncoder_on_rotate);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_rotate_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Assign new callback */
    self->on_rotate_clock_wise = NULL;

    /* If pins' callbacks still set by the other direction */
    if (self->on_rotate_counter_clock_wise)
        return kb_OKAY;

    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_clock;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                            PIN_CLOCK,
                            &pin_clock);

    /* Unset wrapper callback of pin */
    kb_rpi2_Pin_unbind_on_low(pin_clock);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_bind_on_rotate_counter_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self,
    kb_Error (*on_rotate_counter_clock_wise)(kb_rpi2_sensors_RotaryEncoder *const,
                                             kb_rpi2_Event                 *const,
                                             kb_rpi2_Context               *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_rotate_counter_clock_wise)
        return kb_ARG2_IS_NULL;

    /* Assign new callback */
    self->on_rotate_counter_clock_wise = on_rotate_counter_clock_wise;

    /* If pins' callbacks already set by the other direction */
    if (self->on_rotate_clock_wise)
        return kb_OKAY;

    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_clock;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                            PIN_CLOCK,
                            &pin_clock);

    /* Set wrapper callback to pin */
    kb_rpi2_Pin_bind_on_low(pin_clock, RotaryEncoder_on_rotate);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RotaryEncoder_unbind_on_rotate_counter_clock_wise(
    kb_rpi2_sensors_RotaryEncoder *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Assign new callback */
    self->on_rotate_counter_clock_wise = NULL;

    /* If pins' callbacks still set by the other direction */
    if (self->on_rotate_clock_wise)
        return kb_OKAY;

    /* Set wrapper callback to Pin object */
    kb_rpi2_Pin *pin_clock;
    kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,
                            PIN_CLOCK,
                            &pin_clock);

    /* Unet wrapper callback to pin */
    kb_rpi2_Pin_unbind_on_low(pin_clock);

    /* If everything went fine */
    return kb_OKAY;
}
