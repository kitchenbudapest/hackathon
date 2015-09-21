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
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Event
            kb_rpi2_Context */
#include <kb/rpi2/pins.h>
/*  const : kb_rpi2_Pin_OUTPUT
            kb_rpi2_Pin_INPUT
            kb_rpi2_Pin_HIGH
            kb_rpi2_Pin_LOW
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_bind_on_high */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Sensor_ini
            kb_rpi2_Sensor_fin
            kb_rpi2_Sensor_get_pin */
#include <kb/rpi2/sensors/four_keys.h>
/*  type  : kb_rpi2_sensors_FourKeys */


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
/* Role values */
static kb_rpi2_PinRole pin_roles[] =
{
    kb_rpi2_Pin_OUTPUT,
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_INPUT,
    kb_rpi2_Pin_INPUT,
};
/* Initial states */
static kb_rpi2_PinState pin_states[] =
{
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_HIGH,
    kb_rpi2_Pin_HIGH,
    kb_rpi2_Pin_HIGH,
    kb_rpi2_Pin_HIGH,
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
        (void)pin;                                                             \
        /* If `sensor` is NULL */                                              \
        if (!sensor)                                                           \
            return kb_ARG2_IS_NULL;                                            \
        /* Call original callback */                                           \
        return ((kb_rpi2_sensors_FourKeys *const)sensor)->on_key_##KEY(        \
            (kb_rpi2_sensors_FourKeys *const)sensor,                           \
            event,                                                             \
            context);                                                          \
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
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `event` is NULL */
    if (!event)
        return kb_ARG2_IS_NULL;

    /* Create new instance */
    kb_rpi2_sensors_FourKeys *four_keys;
    if (!(four_keys = malloc(sizeof(kb_rpi2_sensors_FourKeys))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_FourKeys_ini(four_keys,
                                              event,
                                              pin_row,
                                              pin_col1,
                                              pin_col2,
                                              pin_col3,
                                              pin_col4)))
    {
        free(four_keys);
        return error;
    }

    /*
     * TODO: set PIN_ROW to output and HIGH
     */

    /* If everything went fine, return values */
    *self = four_keys;
    return kb_OKAY;
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

    /* Initialize instance as Sensor */
    kb_Error error;
    if ((error = kb_rpi2_Sensor_ini((kb_rpi2_Sensor *const)self,
                                    event,
                                    (sizeof pin_ids)/sizeof(kb_rpi2_PinId),
                                    pin_ids,
                                    pin_roles,
                                    pin_states)))
        return error;

    /* Set static values */
    self->on_key_1 = NULL;
    self->on_key_2 = NULL;
    self->on_key_3 = NULL;
    self->on_key_4 = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_fin(kb_rpi2_sensors_FourKeys *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_FourKeys_del(kb_rpi2_sensors_FourKeys **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_FourKeys_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_KEY_X_BIND_FUNCTION(KEY)                                            \
    kb_Error                                                                   \
    kb_rpi2_sensors_FourKeys_bind_on_key_##KEY(                                \
        kb_rpi2_sensors_FourKeys *const  self,                                 \
        kb_Error (*on_key_##KEY)(kb_rpi2_sensors_FourKeys *const,              \
                                 kb_rpi2_Event            *const,              \
                                 kb_rpi2_Context          *const))             \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
        else if (!on_key_##KEY)                                                \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_key_##KEY = on_key_##KEY;                                     \
        /* Set wrapper callback to Pin object */                               \
        kb_rpi2_Pin *pin;                                                      \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,                    \
                               PIN_COL##KEY,                                   \
                               &pin);                                          \
        kb_rpi2_Pin_bind_on_high(pin, FourKeys_on_key_##KEY);                  \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
ON_KEY_X_BIND_FUNCTION(1)
ON_KEY_X_BIND_FUNCTION(2)
ON_KEY_X_BIND_FUNCTION(3)
ON_KEY_X_BIND_FUNCTION(4)



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define ON_KEY_X_UNBIND_FUNCTION(KEY)                                          \
    kb_Error                                                                   \
    kb_rpi2_sensors_FourKeys_unbind_on_key_##KEY(                              \
        kb_rpi2_sensors_FourKeys *const  self,                                 \
        kb_Error (*on_key_##KEY)(kb_rpi2_sensors_FourKeys *const,              \
                                 kb_rpi2_Event            *const,              \
                                 kb_rpi2_Context          *const))             \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
        else if (!on_key_##KEY)                                                \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Assign new callback */                                              \
        self->on_key_##KEY = NULL;                                             \
        /* Set wrapper callback to Pin object */                               \
        kb_rpi2_Pin *pin;                                                      \
        kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,                    \
                               PIN_COL##KEY,                                   \
                               &pin);                                          \
        kb_rpi2_Pin_unbind_on_high(pin);                                       \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create unbinding functions */
ON_KEY_X_UNBIND_FUNCTION(1)
ON_KEY_X_UNBIND_FUNCTION(2)
ON_KEY_X_UNBIND_FUNCTION(3)
ON_KEY_X_UNBIND_FUNCTION(4)
