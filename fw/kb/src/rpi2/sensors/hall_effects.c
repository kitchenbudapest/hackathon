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
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Sensor_ini
            kb_rpi2_Sensor_fin
            kb_rpi2_Sensor_get_pin */
#include <kb/rpi2/pins.h>
/*  const : kb_rpi2_Pin_INPUT
            kb_rpi2_Pin_UNSET
            kb_rpi2_Pin_DOWN
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_bind_on_high
            kb_rpi2_Pin_bind_on_low */
#include <kb/rpi2/sensors/hall_effects.h>
/*  type  : kb_rpi2_sensors_HallEffect */


/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN1 = 0,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
    kb_rpi2_Pin_INPUT,
};
/* Initial pulls */
static kb_rpi2_PinPull PIN_PULLS[] =
{
    kb_rpi2_Pin_DOWN,
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_UNSET,
};


/*----------------------------------------------------------------------------*/
/* Callback wrapper */
#define ON_STATE_FUNCTION(STATE)                                               \
    static kb_Error                                                            \
    HallEffect_on_##STATE(kb_rpi2_Pin     *const pin,                          \
                          kb_rpi2_Sensor  *const sensor,                       \
                          kb_rpi2_Event   *const event,                        \
                          kb_rpi2_Context *const context)                      \
    {                                                                          \
        (void)pin;                                                             \
        /* If `sensor` is NULL */                                              \
        if (!sensor)                                                           \
            return kb_ARG2_IS_NULL;                                            \
        /* Call original callback */                                           \
        return ((kb_rpi2_sensors_HallEffect *const)sensor)->on_##STATE(        \
            (kb_rpi2_sensors_HallEffect *const)sensor,                         \
            event,                                                             \
            context);                                                          \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Callback wrappers */
ON_STATE_FUNCTION(magnetize)
ON_STATE_FUNCTION(demagnetize)
#undef ON_STATE_FUNCTION


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_HallEffect_new(kb_rpi2_sensors_HallEffect **const self,
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
    kb_rpi2_sensors_HallEffect *hall_effect;
    if (!(hall_effect = malloc(sizeof(kb_rpi2_sensors_HallEffect))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_HallEffect_ini(hall_effect, event, pin_id)))
    {
        free(hall_effect);
        return error;
    }

    /* If everything went fine, return values */
    *self = hall_effect;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_HallEffect_ini(kb_rpi2_sensors_HallEffect *const self,
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
kb_rpi2_sensors_HallEffect_fin(kb_rpi2_sensors_HallEffect *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_HallEffect_del(kb_rpi2_sensors_HallEffect **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_HallEffect_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_STATE_BIND_FUNCTION(STATE, PIN_STATE)                               \
    kb_Error                                                                   \
    kb_rpi2_sensors_HallEffect_bind_on_##STATE(                                \
        kb_rpi2_sensors_HallEffect *const  self,                               \
        kb_Error (*on_##STATE)(kb_rpi2_sensors_HallEffect *const,              \
                               kb_rpi2_Event              *const,              \
                               kb_rpi2_Context            *const))             \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
        else if (!on_##STATE)                                                  \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_##STATE = on_##STATE;                                         \
        /* Set wrapper callback to Pin object */                               \
        kb_rpi2_Pin *pin;                                                      \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,                    \
                               PIN1,                                           \
                               &pin);                                          \
        kb_rpi2_Pin_bind_on_##PIN_STATE(pin, HallEffect_on_##STATE);           \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
ON_STATE_BIND_FUNCTION(magnetize, low)
ON_STATE_BIND_FUNCTION(demagnetize, high)
#undef ON_STATE_BIND_FUNCTION


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_STATE_UNBIND_FUNCTION(STATE, PIN_STATE)                             \
    kb_Error                                                                   \
    kb_rpi2_sensors_HallEffect_unbind_on_##STATE(                              \
        kb_rpi2_sensors_HallEffect *const self)                                \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_##STATE = NULL;                                               \
        /* Set wrapper callback to Pin object */                               \
        kb_rpi2_Pin *pin;                                                      \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,                    \
                               PIN1,                                           \
                               &pin);                                          \
        kb_rpi2_Pin_unbind_on_##PIN_STATE(pin);                                \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
ON_STATE_UNBIND_FUNCTION(magnetize, low)
ON_STATE_UNBIND_FUNCTION(demagnetize, high)
#undef ON_STATE_UNBIND_FUNCTION
