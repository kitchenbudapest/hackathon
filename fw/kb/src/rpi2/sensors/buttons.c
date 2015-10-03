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
#include <kb/rpi2/sensors/buttons.h>
/*  type  : kb_rpi2_sensors_Button */


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
#define ON_ACTION_FUNCTION(ACTION)                                             \
    static kb_Error                                                            \
    Button_on_##ACTION(kb_rpi2_Pin     *const pin,                             \
                       kb_rpi2_Sensor  *const sensor,                          \
                       kb_rpi2_Event   *const event,                           \
                       kb_rpi2_Context *const context)                         \
    {                                                                          \
        (void)pin;                                                             \
        /* If `sensor` is NULL */                                              \
        if (!sensor)                                                           \
            return kb_ARG2_IS_NULL;                                            \
        /* Call original callback */                                           \
        return ((kb_rpi2_sensors_Button *const)sensor)->on_##ACTION(           \
            (kb_rpi2_sensors_Button *const)sensor,                             \
            event,                                                             \
            context);                                                          \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Callback wrappers */
ON_ACTION_FUNCTION(press)
ON_ACTION_FUNCTION(release)
#undef ON_ACTION_FUNCTION


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_Button_new(kb_rpi2_sensors_Button **const self,
                           kb_rpi2_Event           *const event,
                           kb_rpi2_PinId                  pin_id)
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
    kb_rpi2_sensors_Button *button;
    if (!(button = malloc(sizeof(kb_rpi2_sensors_Button))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_Button_ini(button, event, pin_id)))
    {
        free(button);
        return error;
    }

    /* If everything went fine, return values */
    *self = button;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_ini(kb_rpi2_sensors_Button *const self,
                           kb_rpi2_Event          *const event,
                           kb_rpi2_PinId                 pin_id)
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

    /* Initialize data */
    self->on_press   = NULL;
    self->on_release = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_fin(kb_rpi2_sensors_Button *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_Button_del(kb_rpi2_sensors_Button **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_Button_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_ACTION_BIND_FUNCTION(ACTION, PIN_STATE)                             \
    kb_Error                                                                   \
    kb_rpi2_sensors_Button_bind_on_##ACTION(                                   \
        kb_rpi2_sensors_Button *const  self,                                   \
        kb_Error (*on_##ACTION)(kb_rpi2_sensors_Button *const,                 \
                                kb_rpi2_Event          *const,                 \
                                kb_rpi2_Context        *const))                \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
        else if (!on_##ACTION)                                                 \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_##ACTION = on_##ACTION;                                       \
        /* Set wrapper callback to Pin object */                               \
        kb_rpi2_Pin *pin;                                                      \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,                    \
                               PIN1,                                           \
                               &pin);                                          \
        kb_rpi2_Pin_bind_on_##PIN_STATE(pin, Button_on_##ACTION);              \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
ON_ACTION_BIND_FUNCTION(press, high)
ON_ACTION_BIND_FUNCTION(release, low)
#undef ON_ACTION_BIND_FUNCTION


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_ACTION_UNBIND_FUNCTION(ACTION, PIN_STATE)                           \
    kb_Error                                                                   \
    kb_rpi2_sensors_Button_unbind_on_##ACTION(                                 \
        kb_rpi2_sensors_Button *const self)                                    \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_##ACTION = NULL;                                              \
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
ON_ACTION_UNBIND_FUNCTION(press, high)
ON_ACTION_UNBIND_FUNCTION(release, low)
#undef ON_ACTION_UNBIND_FUNCTION
