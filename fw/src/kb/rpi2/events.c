/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */
#include <stdlib.h>
/*  func  : malloc
            free */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL */
#include <kb/utils/dense_set.h>
/*  macro : KB_UTILS_DENSE_SET_ITEM_MEMBERS
    type  : kb_utils_DenseSet
            kb_utils_DenseSetItem
            kb_utils_DenseSetIter
    func  : kb_utils_DenseSet_new
            kb_utils_DenseSet_del
            kb_utils_DenseSet_push
            kb_utils_DenseSet_pull
            kb_utils_DenseSetIter_new
            kb_utils_DenseSetIter_del
            kb_utils_DenseSetIter_next */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  : kb_rpi2_Context_activate_event */
#include <kb/rpi2/events.h>
/*  macro : KB_RPI2_PINS_COUNT
    type  : kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    func  : kb_rpi2_Sensor_disable */
#include <kb/rpi2/pins.h>
/*  type  : kb_rpi2_Pin
    func  : kb_rpi2_Pin_new
            kb_rpi2_Pin_del
            kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low */


/*----------------------------------------------------------------------------*/
#define INITIAL_SENSORS_LIMIT (size_t)32


/*----------------------------------------------------------------------------*/
#define KB_RPI2_CHECK_PIN_ID_IN_RANGE(P)                                       \
    if ((size_t)P < (size_t)0 &&                                               \
        (size_t)P >= KB_RPI2_PINS_COUNT)                                       \
        return kb_INVALID_PIN_ID;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Event_new(kb_rpi2_Event   **const self,
                  kb_rpi2_Context  *const context)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If `context` is NULL */
    if (!context)
        return kb_ARG2_IS_NULL;

    /* Create new Event object */
    kb_rpi2_Event *event;
    if (!(event = malloc(sizeof(kb_rpi2_Event))))
        return kb_ALLOC_FAIL;

    /* Initialize new Event object */
    if (kb_rpi2_Event_ini(event, context))
    {
        free(event);
        return kb_ALLOC_FAIL;
    }

    /* If everything went fine, return values */
    *self = event;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_ini(kb_rpi2_Event   *const self,
                  kb_rpi2_Context *const context)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!context)
        return kb_ARG2_IS_NULL;

    /* Treat Event object as a DenseSetItem */
    kb_utils_DenseSetItem_ini((kb_utils_DenseSetItem *const)self);

    /* Create new DenseSet object */
    if (kb_utils_DenseSet_new(&(self->sensors), INITIAL_SENSORS_LIMIT))
        return kb_ALLOC_FAIL;

    /* "Zero out" all Pin objects in the array */
    for (size_t i=0; i<KB_RPI2_PINS_COUNT; i++)
        self->pins[i] = NULL;

    /* Set values */
    self->context = context;
    kb_rpi2_Context_bind_event(context, self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_fin(kb_rpi2_Event *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Delete all Pins objects in the array */
    kb_rpi2_Pin **pins = self->pins;
    for (size_t i=0; i<KB_RPI2_PINS_COUNT; i++)
        kb_rpi2_Pin_del(pins + i);

    /* Delete DenseSet object */
    kb_utils_DenseSet_del(&(self->sensors));

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_del(kb_rpi2_Event **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_Event_fin(*self);

    /* Deallocate instance and redirect self */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_callback_args(kb_rpi2_Event    *const self,
                            kb_rpi2_Context **const context)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!context)
        return kb_ARG2_IS_NULL;

    /* Return context */
    *context = self->context;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_activate(kb_rpi2_Event *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Propagate other errors */
    return kb_rpi2_Context_activate_event(self->context, self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_use_pin(kb_rpi2_Event  *const self,
                      kb_rpi2_PinId         pin_id,
                      kb_rpi2_Sensor *const sensor)
{
    /* If any of the arguments iis NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!sensor)
        return kb_ARG3_IS_NULL;

    /* Check validity of `pin_id` */
    KB_RPI2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* If `sensor` is not bound to this Event object */
    if (sensor->event != self)
        return kb_SENSOR_IS_NOT_IN_EVENT;

    /* If this Event object is already using this Pin object */
    if (self->pins[pin_id])
        return kb_PIN_ALREADY_USED;

    /* Store `sensor` */
    if (kb_utils_DenseSet_push(self->sensors, (kb_utils_DenseSetItem *const)sensor))
        return kb_ALLOC_FAIL;

    /* Create new Pin object */
    return kb_rpi2_Pin_new(self->pins + pin_id, pin_id, sensor);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_drop_pin(kb_rpi2_Event *const self,
                       kb_rpi2_PinId        pin_id)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Check validity of `pin_id` */
    KB_RPI2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Delete Pin object */
    kb_rpi2_Pin_del(self->pins + pin_id);

    /* Remove pin */
    self->pins[pin_id] = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_high(kb_rpi2_Event *const self,
                           kb_rpi2_PinId        pin_id)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Check validity of `pin_id` */
    KB_RPI2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Set pin to HIGH */
    switch (kb_rpi2_Pin_set_high(self->pins[pin_id]))
    {
        /* If pin is not used */
        case kb_SELF_IS_NULL:
            return kb_PIN_DOES_NOT_EXIST;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_set_pin_low(kb_rpi2_Event *const self,
                          kb_rpi2_PinId        pin_id)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Check validity of `pin_id` */
    KB_RPI2_CHECK_PIN_ID_IN_RANGE(pin_id);

    /* Set pin to LOW */
    switch (kb_rpi2_Pin_set_low(self->pins[pin_id]))
    {
        /* If pin is not used */
        case kb_SELF_IS_NULL:
            return kb_PIN_DOES_NOT_EXIST;

        /* If everything went fine */
        default:
            return kb_OKAY;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_reset_all_pins(kb_rpi2_Event *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Iterate through all pins and reset all of them */
    for (size_t i=0; i<KB_RPI2_PINS_COUNT; i++)
        kb_rpi2_Pin_reset(self->pins[i]);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_bind_sensor(kb_rpi2_Event  *const self,
                          kb_rpi2_Sensor *const sensor)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Store sensor and propagate errors */
    return kb_utils_DenseSet_push(self->sensors,
                                  (kb_utils_DenseSetItem *const)sensor);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_unbind_sensor(kb_rpi2_Event  *const self,
                            kb_rpi2_Sensor *const sensor)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Remove sensor and propagate errors */
    return kb_utils_DenseSet_pull(self->sensors,
                                  (kb_utils_DenseSetItem *const)sensor);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_disable_all_sensors(kb_rpi2_Event *const self)
{
    /* Local variables */
    kb_Error               error;
    kb_utils_DenseSetIter *iter;
    kb_utils_DenseSetItem *sensor;

    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Create new Iterator object */
    if ((error = kb_utils_DenseSetIter_new(&iter, self->sensors)))
        return error;

    /* Iterate through all bound sensors */
    kb_utils_DenseSetIter_next(iter, &sensor);
    while (sensor)
    {
        /* Disable each sensor */
        kb_rpi2_Sensor_disable((kb_rpi2_Sensor *const)sensor);
        kb_utils_DenseSetIter_next(iter, &sensor);
    }

    /* Delete Iterator object */
    kb_utils_DenseSetIter_del(&iter);

    /* If everything went fine */
    return kb_OKAY;
}
