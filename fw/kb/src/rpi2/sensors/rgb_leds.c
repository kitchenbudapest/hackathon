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
            kb_rpi2_Pin_LOW
            kb_rpi2_Pin_OFF
    type  : kb_rpi2_Pin
            kb_rpi2_PinId
            kb_rpi2_PinRole
            kb_rpi2_PinState
    func  : kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low */
#include <kb/rpi2/sensors/rgb_leds.h>
/*  type  : kb_rpi2_sensors_RGBLED */


/*----------------------------------------------------------------------------*/
/* Index shortcuts */
enum pin_indices
{
    PIN_RED = 0,
    PIN_GREEN,
    PIN_BLUE,
    PIN_COUNT,
};
/* Role values */
static kb_rpi2_PinRole PIN_ROLES[] =
{
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
};
/* Initial states */
static kb_rpi2_PinState PIN_STATES[] =
{
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_LOW,
};


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_sensors_RGBLED_new(kb_rpi2_sensors_RGBLED **const self,
                           kb_rpi2_Event           *const event,
                           kb_rpi2_PinId                  pin_red,
                           kb_rpi2_PinId                  pin_green,
                           kb_rpi2_PinId                  pin_blue)
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
    kb_rpi2_sensors_RGBLED *rgb_led;
    if (!(rgb_led = malloc(sizeof(kb_rpi2_sensors_RGBLED))))
        return kb_ALLOC_FAIL;

    /* Initialize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_RGBLED_ini(rgb_led,
                                            event,
                                            pin_red,
                                            pin_green,
                                            pin_blue)))
    {
        free(rgb_led);
        return error;
    }

    /* If everything went fine, return values */
    *self = rgb_led;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_ini(kb_rpi2_sensors_RGBLED *const self,
                           kb_rpi2_Event          *const event,
                           kb_rpi2_PinId                 pin_red,
                           kb_rpi2_PinId                 pin_green,
                           kb_rpi2_PinId                 pin_blue)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;

    /* Create array from arguments */
    kb_rpi2_PinId pin_ids[] =
    {
        pin_red,
        pin_green,
        pin_blue,
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
kb_rpi2_sensors_RGBLED_fin(kb_rpi2_sensors_RGBLED *const self)
{
    /* Finalize instance as Sensor */
    return kb_rpi2_Sensor_fin((kb_rpi2_Sensor *const)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_RGBLED_del(kb_rpi2_sensors_RGBLED **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_Error error;
    if ((error = kb_rpi2_sensors_RGBLED_fin(*self)))
        return error;

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define SINGLE_PIN(COLOR, PIN)                                                 \
    kb_Error                                                                   \
    kb_rpi2_sensors_RGBLED_##COLOR(kb_rpi2_sensors_RGBLED *const self)         \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Iterate through all pins */                                         \
        kb_rpi2_Pin *pin;                                                      \
        kb_Error     error;                                                    \
        for (int i=0; i<PIN_COUNT; i++)                                        \
        {                                                                      \
            /* Get pin */                                                      \
            if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,   \
                                                (size_t)i,                     \
                                                &pin)))                        \
                return error;                                                  \
                                                                               \
            /* If set this pin to HIGH */                                      \
            if (i == PIN)                                                      \
                kb_rpi2_Pin_set_high(pin);                                     \
            /* If set this pin to LOW */                                       \
            else                                                               \
                kb_rpi2_Pin_set_low(pin);                                      \
        }                                                                      \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
SINGLE_PIN(red, PIN_RED)
SINGLE_PIN(green, PIN_GREEN)
SINGLE_PIN(blue, PIN_BLUE)
#undef SINGLE_PIN


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define DOUBLE_PINS(COLOR, PIN1, PIN2)                                         \
    kb_Error                                                                   \
    kb_rpi2_sensors_RGBLED_##COLOR(kb_rpi2_sensors_RGBLED *const self)         \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Iterate through all pins */                                         \
        kb_rpi2_Pin *pin;                                                      \
        kb_Error     error;                                                    \
        for (int i=0; i<PIN_COUNT; i++)                                        \
        {                                                                      \
            /* Get pin */                                                      \
            if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,   \
                                                (size_t)i,                     \
                                                &pin)))                        \
                return error;                                                  \
                                                                               \
            /* If set this pin to HIGH */                                      \
            if (i == PIN1 ||                                                   \
                i == PIN2)                                                     \
                kb_rpi2_Pin_set_high(pin);                                     \
            /* If set this pin to LOW */                                       \
            else                                                               \
                kb_rpi2_Pin_set_low(pin);                                      \
        }                                                                      \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
DOUBLE_PINS(yellow, PIN_RED, PIN_GREEN)
DOUBLE_PINS(magenta, PIN_RED, PIN_BLUE)
DOUBLE_PINS(cyan, PIN_BLUE, PIN_GREEN)
#undef DOUBLE_PINS


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define TRIPLE_PINS(COLOR, STATE)                                              \
    kb_Error                                                                   \
    kb_rpi2_sensors_RGBLED_##COLOR(kb_rpi2_sensors_RGBLED *const self)         \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Iterate through all pins */                                         \
        kb_rpi2_Pin *pin;                                                      \
        kb_Error     error;                                                    \
        for (int i=0; i<PIN_COUNT; i++)                                        \
        {                                                                      \
            /* Get pin */                                                      \
            if ((error = kb_rpi2_Sensor_get_pin((kb_rpi2_Sensor *const)self,   \
                                                (size_t)i,                     \
                                                &pin)))                        \
                return error;                                                  \
            /* Set pin HIGH */                                                 \
            kb_rpi2_Pin_set_##STATE(pin);                                      \
        }                                                                      \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
TRIPLE_PINS(white, high)
TRIPLE_PINS(black, low)
#undef TRIPLE_PINS
