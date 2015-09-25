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
#ifdef __arm__
    /* Include bcm2835 headers */
    #include <bcm2835.h>
    /*  const : RPI_BPLUS_GPIO_J8_*
        func  : bcm2835_init
                bcm2835_close */
#endif /* __arm__ */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ARG3_IS_NULL
            kb_ALLOC_FAIL */
#include <kb/rpi2/pins.h>
/*  type  : kb_rpi2_PinRole
            kb_rpi2_PinState
            kb_rpi2_PinId
    const : kb_rpi2_Pin_OUTPUT
            kb_rpi2_Pin_INPUT
            kb_rpi2_Pin_LOW
            kb_rpi2_Pin_HIGH */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
#define kb_rpi2_CHECK_SELF_IS_NULL(S)                                          \
    if (!S)                                                                    \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
#ifdef __arm__
    /* Pin reference counting */
    static size_t USED_PIN_COUNTER = (size_t)0;

    /* J8 -> kb_rpi2_PINx */
    #define INVALID_PIN_GND0 -1
    #define INVALID_PIN_PWR3 -2
    #define INVALID_PIN_PWR5 -3
    #define INVALID_PIN_RSVD -4
    static const int PIN_CONVERSION[] =
    {
        [kb_rpi2_PIN1]  = INVALID_PIN_PWR3,
        [kb_rpi2_PIN2]  = INVALID_PIN_PWR5,
        [kb_rpi2_PIN3]  = RPI_BPLUS_GPIO_J8_03,
        [kb_rpi2_PIN4]  = INVALID_PIN_PWR5,
        [kb_rpi2_PIN5]  = RPI_BPLUS_GPIO_J8_05,
        [kb_rpi2_PIN6]  = INVALID_PIN_GND0,
        [kb_rpi2_PIN7]  = INVALID_PIN_RSVD,
        [kb_rpi2_PIN8]  = INVALID_PIN_RSVD,
        [kb_rpi2_PIN9]  = INVALID_PIN_GND0,
        [kb_rpi2_PIN10] = INVALID_PIN_RSVD,

        [kb_rpi2_PIN11] = RPI_BPLUS_GPIO_J8_11,
        [kb_rpi2_PIN12] = RPI_BPLUS_GPIO_J8_12,
        [kb_rpi2_PIN13] = RPI_BPLUS_GPIO_J8_13,
        [kb_rpi2_PIN14] = INVALID_PIN_GND0,
        [kb_rpi2_PIN15] = RPI_BPLUS_GPIO_J8_15,
        [kb_rpi2_PIN16] = RPI_BPLUS_GPIO_J8_16,
        [kb_rpi2_PIN17] = INVALID_PIN_PWR3,
        [kb_rpi2_PIN18] = RPI_BPLUS_GPIO_J8_18,
        [kb_rpi2_PIN19] = RPI_BPLUS_GPIO_J8_19,
        [kb_rpi2_PIN20] = INVALID_PIN_GND0,

        [kb_rpi2_PIN21] = RPI_BPLUS_GPIO_J8_21,
        [kb_rpi2_PIN22] = RPI_BPLUS_GPIO_J8_22,
        [kb_rpi2_PIN23] = RPI_BPLUS_GPIO_J8_23,
        [kb_rpi2_PIN24] = RPI_BPLUS_GPIO_J8_24,
        [kb_rpi2_PIN25] = INVALID_PIN_GND0,
        [kb_rpi2_PIN26] = RPI_BPLUS_GPIO_J8_26,
        [kb_rpi2_PIN27] = INVALID_PIN_RSVD,
        [kb_rpi2_PIN28] = INVALID_PIN_RSVD,
        [kb_rpi2_PIN29] = RPI_BPLUS_GPIO_J8_29,
        [kb_rpi2_PIN30] = INVALID_PIN_GND0,

        [kb_rpi2_PIN31] = RPI_BPLUS_GPIO_J8_31,
        [kb_rpi2_PIN32] = RPI_BPLUS_GPIO_J8_32,
        [kb_rpi2_PIN33] = RPI_BPLUS_GPIO_J8_33,
        [kb_rpi2_PIN34] = INVALID_PIN_GND0,
        [kb_rpi2_PIN35] = RPI_BPLUS_GPIO_J8_35,
        [kb_rpi2_PIN36] = RPI_BPLUS_GPIO_J8_36,
        [kb_rpi2_PIN37] = RPI_BPLUS_GPIO_J8_37,
        [kb_rpi2_PIN38] = RPI_BPLUS_GPIO_J8_38,
        [kb_rpi2_PIN39] = INVALID_PIN_GND0,
        [kb_rpi2_PIN40] = RPI_BPLUS_GPIO_J8_40,
    };
#endif /* __arm__ */


/*----------------------------------------------------------------------------*/
static inline kb_Error
kb_rpi2_Pins_initialize(void)
{
    #ifdef __arm__
        /* If this is the first Pin object created in this session,
       or the first one created after a session already finished */
        if (!(USED_PIN_COUNTER++) &&
            !bcm2835_init())
                return kb_BCM2835_INIT_FAIL;
    #endif /* __arm__ */
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
static inline kb_Error
kb_rpi2_Pins_finalize(void)
{
    #ifdef __arm__
        /* If this is the last finalization call in a session */
        if (!(--USED_PIN_COUNTER))
            bcm2835_close();
    #endif /* __arm__ */
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Pin_new(kb_rpi2_Pin      **const self,
                kb_rpi2_PinId            pin_id,
                kb_rpi2_PinRole          pin_role,
                kb_rpi2_PinPull          pin_pull,
                kb_rpi2_PinState         pin_state,
                kb_rpi2_Sensor    *const sensor)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `sensor` is NULL */
    if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Create new Pin object */
    kb_rpi2_Pin *pin;
    if (!(pin = malloc(sizeof(kb_rpi2_Pin))))
        return kb_ALLOC_FAIL;

    /* Initialize new Pin object */
    kb_Error error;
    if ((error = kb_rpi2_Pin_ini(pin,
                                 pin_id,
                                 pin_role,
                                 pin_pull,
                                 pin_state,
                                 sensor)))
    {
        free(pin);
        return error;
    }

    /* If everything went fine, return values */
    *self = pin;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_ini(kb_rpi2_Pin      *const self,
                kb_rpi2_PinId           pin_id,
                kb_rpi2_PinRole         pin_role,
                kb_rpi2_PinPull         pin_pull,
                kb_rpi2_PinState        pin_state,
                kb_rpi2_Sensor   *const sensor)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Initialize low level access */
    kb_Error error;
    if ((error = kb_rpi2_Pins_initialize()))
        return error;

    #ifdef __arm__
        /* Get bcm pin representation */
        RPiGPIOPin bcm_pin;
        switch (PIN_CONVERSION[pin_id])
        {
            case INVALID_PIN_GND0:
                return kb_PIN_IS_GROUND;

            case INVALID_PIN_PWR3:
                return kb_PIN_IS_POWER_V3_3;

            case INVALID_PIN_PWR5:
                return kb_PIN_IS_POWER_V5;

            case INVALID_PIN_RSVD:
                return kb_PIN_IS_RESERVED;

            default:
                bcm_pin = PIN_CONVERSION[pin_id];
        }

        /* Set PinPull */
        switch (pin_pull)
        {
            case kb_rpi2_Pin_OFF:
                bcm2835_gpio_set_pud(bcm_pin, BCM2835_GPIO_PUD_OFF);
                break;

            case kb_rpi2_Pin_UP:
                bcm2835_gpio_set_pud(bcm_pin, BCM2835_GPIO_PUD_UP);
                break;

            case kb_rpi2_Pin_DOWN:
                bcm2835_gpio_set_pud(bcm_pin, BCM2835_GPIO_PUD_DOWN);
                break;

            default:
                return kb_INVALID_PIN_PULL;
        }

        /* Set PinRole */
        switch (pin_role)
        {
            case kb_rpi2_Pin_OUTPUT:
                bcm2835_gpio_fsel(bcm_pin, BCM2835_GPIO_FSEL_OUTP);
                break;

            case kb_rpi2_Pin_INPUT:
                bcm2835_gpio_fsel(bcm_pin, BCM2835_GPIO_FSEL_INPT);
                break;

            default:
                return kb_INVALID_PIN_ROLE;
        }

        /* Set PinState */
        switch (pin_state)
        {
            case kb_rpi2_Pin_LOW:
                bcm2835_gpio_clr(bcm_pin);
                break;

            case kb_rpi2_Pin_HIGH:
                bcm2835_gpio_set(bcm_pin);
                break;

            default:
                return kb_INVALID_PIN_STATE;
        }
    #endif /* __arm__ */

    /* Initialize Pin object */
    self->id             = pin_id;
    self->role           = pin_role;
    self->pull           = pin_pull;
    self->state          = pin_state;
    self->sensor         = sensor;
    self->on_start       = NULL;
    self->on_stop        = NULL;
    self->on_cycle_begin = NULL;
    self->on_cycle_end   = NULL;
    self->on_high        = NULL;
    self->on_low         = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_fin(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Finalize low level access */
    kb_Error error;
    if ((error = kb_rpi2_Pins_finalize()))
        return error;

    /*
     * TODO: Reset this pin via bcm2835
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_del(kb_rpi2_Pin **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_Pin_fin(*self);

    /* Deallocate instance and redirect self */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_callback_args(kb_rpi2_Pin      *const self,
                          kb_rpi2_Sensor  **const sensor,
                          kb_rpi2_Event   **const event,
                          kb_rpi2_Context **const context)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!sensor)
        return kb_ARG2_IS_NULL;

    /* Set callback arguments */
    *sensor = self->sensor;
    switch (kb_rpi2_Sensor_callback_args(self->sensor, event, context))
    {
        /* If `event` is NULL */
        case kb_ARG2_IS_NULL:
            return kb_ARG3_IS_NULL;

        /* If `context` is NULL */
        case kb_ARG3_IS_NULL:
            return kb_ARG4_IS_NULL;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_reset(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /*
     * TODO: Reset this pin via bcm2835
     *       Reset self->state as well
     */

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_listen(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If signal changed */
    /*
     * TODO: get signal via bcm2835
     */

    /* If the state has been changed */
    kb_rpi2_Event   *event;
    kb_rpi2_Context *context;
    switch (self->state)
    {
        /* If new state is HIGH */
        case kb_rpi2_Pin_HIGH:
            /* If there is an `on_high` callback, call it */
            if (self->on_high)
            {
                /* Get `event` and `context` objects */
                kb_rpi2_Sensor_callback_args(self->sensor,
                                             &event,
                                             &context);
                /* Call callback */
                self->on_high(self,
                              self->sensor,
                              event,
                              context);
            }
            break;

        /* If new state is LOW */
        case kb_rpi2_Pin_LOW:
            /* If there is an `on_high` callback, call it */
            if (self->on_low)
            {
                /* Get `event` and `context` objects */
                kb_rpi2_Sensor_callback_args(self->sensor,
                                             &event,
                                             &context);
                /* Call callback */
                self->on_low(self,
                             self->sensor,
                             event,
                             context);
            }
            break;
    }

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_high(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If a callback set to this pin */
    if (self->on_high)
    {
        /* Get `event` and `context` objects */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_high(self,
                      self->sensor,
                      event,
                      context);
    }

    #ifdef __arm__
        /* Set pin HIGH via bcm2835 */
        bcm2835_gpio_set(PIN_CONVERSION[self->id]);
    #endif /* __arm__ */

    /* Switch state */
    self->state = kb_rpi2_Pin_HIGH;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_set_low(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If a callback set to this pin */
    if (self->on_low)
    {
        /* Get `event` and `context` objects */
        kb_rpi2_Event   *event;
        kb_rpi2_Context *context;
        kb_rpi2_Sensor_callback_args(self->sensor,
                                     &event,
                                     &context);
        /* Call callback */
        self->on_low(self,
                     self->sensor,
                     event,
                     context);
    }

    #ifdef __arm__
        /* Set pin LOW via bcm2835 */
        bcm2835_gpio_clr(PIN_CONVERSION[self->id]);
    #endif /* __arm__ */

    /* Switch state */
    self->state = kb_rpi2_Pin_LOW;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_high(kb_rpi2_Pin  *const self,
                         kb_Error    (*on_high)(kb_rpi2_Pin     *const,
                                                kb_rpi2_Sensor  *const,
                                                kb_rpi2_Event   *const,
                                                kb_rpi2_Context *const))
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If `on_high` is NULL */
    if (!on_high)
        return kb_ARG2_IS_NULL;

    /* Set callback function */
    self->on_high = on_high;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_high(kb_rpi2_Pin *const self)
{
    /* If self is NULL */
    kb_rpi2_CHECK_SELF_IS_NULL(self);

    /* Unset callback function */
    self->on_high = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_bind_on_low(kb_rpi2_Pin  *const self,
                        kb_Error    (*on_low)(kb_rpi2_Pin     *const,
                                              kb_rpi2_Sensor  *const,
                                              kb_rpi2_Event   *const,
                                              kb_rpi2_Context *const))
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If `on_low` is NULL */
    if (!on_low)
        return kb_ARG2_IS_NULL;

    /* Set callback function */
    self->on_low = on_low;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Pin_unbind_on_low(kb_rpi2_Pin *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Unset callback function */
    self->on_low = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* TODO: **Only bind methods are enough**
         unbind methods are unnecessary, as bind_on_x(self, NULL) could do the
         exact same thing, and it eliminates an extra conditional and an extra
         method definition */
#define PIN_LOOP_CALLBACK_BIND(FUNC)                                           \
    kb_Error                                                                   \
    kb_rpi2_Pin_bind_##FUNC(kb_rpi2_Pin *const self,                           \
                            kb_Error (*FUNC)(kb_rpi2_Pin *const))              \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* If `on_low` is NULL */                                              \
        if (!FUNC)                                                             \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Set callback function */                                            \
        self->FUNC = FUNC;                                                     \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
PIN_LOOP_CALLBACK_BIND(on_start)
PIN_LOOP_CALLBACK_BIND(on_stop)
PIN_LOOP_CALLBACK_BIND(on_cycle_begin)
PIN_LOOP_CALLBACK_BIND(on_cycle_end)
#undef PIN_LOOP_CALLBACK_BIND


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PIN_LOOP_CALLBACK_UNBIND(FUNC)                                         \
    kb_Error                                                                   \
    kb_rpi2_Pin_unbind_##FUNC(kb_rpi2_Pin *const self)                         \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Unset callback function */                                          \
        self->FUNC = NULL;                                                     \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
PIN_LOOP_CALLBACK_UNBIND(on_start)
PIN_LOOP_CALLBACK_UNBIND(on_stop)
PIN_LOOP_CALLBACK_UNBIND(on_cycle_begin)
PIN_LOOP_CALLBACK_UNBIND(on_cycle_end)
#undef PIN_LOOP_CALLBACK_UNBIND


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PIN_LOOP_CALLBACK_CALL(FUNC)                                           \
    kb_Error                                                                   \
    kb_rpi2_Pin_##FUNC(kb_rpi2_Pin *const self)                                \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* If instance has `on_FUNC` callback, call it */                      \
        if (self->FUNC)                                                        \
            return self->FUNC(self);                                           \
        /* If not, return */                                                   \
        return kb_OKAY;                                                        \
    }
PIN_LOOP_CALLBACK_CALL(on_start)
PIN_LOOP_CALLBACK_CALL(on_stop)
PIN_LOOP_CALLBACK_CALL(on_cycle_begin)
PIN_LOOP_CALLBACK_CALL(on_cycle_end)
#undef PIN_LOOP_CALLBACK_CALL
