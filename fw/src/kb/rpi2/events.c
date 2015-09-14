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
    func  : kb_utils_DenseSet_new
            kb_utils_DenseSet_del
            kb_utils_DenseSet_push
            kb_utils_DenseSet_pull */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  : kb_rpi2_Context_activate_event */
#include <kb/rpi2/events.h>
/*  macro : KB_RPI2_PIN_COUNT
    type  : kb_rpi2_Event */
#include <kb/rpi2/pins.h>
/*  type  : kb_rpi2_Pin
    func  : kb_rpi2_Pin_new
            kb_rpi2_Pin_del
            kb_rpi2_Pin_set_high
            kb_rpi2_Pin_set_low */


/*----------------------------------------------------------------------------*/
#define INITIAL_SENSORS_LIMIT (size_t)32


/*----------------------------------------------------------------------------*/
#define KB_RPI2_CHECK_SELF_IS_NULL(S)                                          \
    if (!S)                                                                    \
        return kb_SELF_IS_NULL;


/*----------------------------------------------------------------------------*/
#define KB_RPI2_CHECK_PIN_ID_IN_RANGE(P)                                       \
    if (P < 0 &&                                                               \
        P >= KB_RPI2_PIN_COUNT)                                                \
        return kb_INVALID_PIN_ID;


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Event_new(kb_rpi2_Event   **const self,
                  kb_rpi2_Context  *const context)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!context)
        return kb_ARG2_IS_NULL;

    /* Create new Event object */
    kb_rpi2_Event *event;
    if (!(event = malloc(sizeof(kb_rpi2_Event))))
        goto Self_Alloc_Failed;

    /* Create new DenseSet object */
    if (kb_utils_DenseSet_new(&(event->sensors), INITIAL_SENSORS_LIMIT))
        goto Sensors_Alloc_Failed;

    /* "Zero out" all Pin objects in the array */
    for (size_t i=0; i<KB_RPI2_PIN_COUNT; i++)
        event->pins[i] = NULL;

    /* Set values */
    event->context = context;

    /* Return new Event object */
    *self = event;

    /* If everything went fine */
    return kb_OKAY;

    /* If there was an error */
    Sensors_Alloc_Failed:
        free(event);
    Self_Alloc_Failed:
        *self = NULL;
        return kb_ALLOC_FAIL;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_del(kb_rpi2_Event **const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Delete all Pins objects in the array */
    for (size_t i=0; i<KB_RPI2_PIN_COUNT; i++)
        kb_rpi2_Pin_del(self->pins[i]);

    /* Delete DenseSet object */
    kb_utils_DenseSet_del(&(*self)->sensors);

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
    KB_RPI2_CHECK_SELF_IS_NULL(self);

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
    KB_RPI2_CHECK_SELF_IS_NULL(self);

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
    KB_RPI2_CHECK_SELF_IS_NULL(self);

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
kb_rpi2_Event_bind_sensor(kb_rpi2_Event  *const self,
                          kb_rpi2_Sensor *const sensor)
{
    /* If `self` is NULL */
    KB_RPI2_CHECK_SELF_IS_NULL(self);

    /* Resize collection if there is not enough space for one more sensor */
    if (self->sensors_count + 1 >= self->sensors_limit)
    {
        /* Reallocate space for sensor */
        kb_rpi2_Sensor **sensors;
        if (!(sensors = realloc(sizeof(kb_rpi2_Sensor *)*(self->sensors_limit*2)))
            return kb_ALLOC_FAIL;

        /* Store new pointer */
        self->sensors = sensors;
        /* Update limit */
        self->sensors_count *= 2;
    }

    /* Store sensor */
    self->sensors[self->sensors_count] = sensor;
    /* Set sensor id and increase sensor counter */
    sensor->id = self->sensors_count++;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_unbind_sensor(kb_rpi2_Event  *const self,
                            kb_rpi2_Sensor *const sensor)
{
    /* If everything went fine */
    return kb_OKAY;
}
