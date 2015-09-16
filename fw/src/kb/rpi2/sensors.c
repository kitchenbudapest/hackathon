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
    const : kb_OKAY */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Sensor
            kb_rpi2_Event
            kb_rpi2_Context */
#include <kb/rpi2/events.h>
/*  macro : KB_RPI2_PINS_COUNT
    type  : kb_rpi2_Event */


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Sensor_new(kb_rpi2_Sensor **const self,
                   kb_rpi2_Event   *const event,
                   size_t                 pin_ids_count,
                   kb_rpi2_PinId   *const pin_ids)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* If any of the arguments is NULL */
    if (!event)
        return kb_ARG2_IS_NULL;
    else if (!pin_ids)
        return kb_ARG4_IS_NULL;

    /* Create new instance */
    kb_rpi2_Sensor *sensor;
    if (!(sensor = malloc(sizeof(kb_rpi2_Sensor))))
        return kb_ALLOC_FAIL;

    /* Initialize new instance */
    kb_Error error;
    if ((error = kb_rpi2_Sensor_ini(sensor, event, pin_ids_count, pin_ids)))
        return error;

    /* If everything went fine */
    *self = sensor;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_ini(kb_rpi2_Sensor *const self,
                   kb_rpi2_Event  *const event,
                   size_t                pin_ids_count,
                   kb_rpi2_PinId  *const pin_ids)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;
    else if (!pin_ids)
        return kb_ARG4_IS_NULL;

    /* If too many `pin_id`s passed */
    if (pin_ids_count > KB_RPI2_PINS_COUNT)
        return kb_TOO_MANY_PINS_USED;

    /* Create storage for `pin_id`s */
    if (!(self->pin_ids = malloc(sizeof(kb_rpi2_PinId)*pin_ids_count)))
        return kb_ALLOC_FAIL;

    /* Store `pin_id`s and "reserve" pins */
    kb_Error error;
    for (size_t i=0; i<pin_ids_count; i++)
    {
        self->pin_ids[i] = pin_ids[i];
        if ((error = kb_rpi2_Event_use_pin(event, pin_ids[i], self)))
            return error;
    }

    /* Store static data */
    self->pin_ids_count = pin_ids_count;
    self->event         = event;
    self->state         = kb_rpi2_Sensor_DISABLED;
    self->on_enable     = NULL;
    self->on_disable    = NULL;

    /* Make the connection */
    kb_rpi2_Event_bind_sensor(event, self);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_fin(kb_rpi2_Sensor *const self)
{
    /* If `self` or instance is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Release pins */
    for (size_t i=0; i<self->pin_ids_count; i++)
        kb_rpi2_Event_drop_pin(self->event, self->pin_ids[i]);

    /* Break the connection */
    kb_rpi2_Event_unbind_sensor(self->event, self);

    /* Deallocate spaces and instance */
    free(self->pin_ids);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_del(kb_rpi2_Sensor **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_Sensor_fin(*self);

    /* Deallocate instance */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_callback_args(kb_rpi2_Sensor   *const self,
                             kb_rpi2_Event   **const event,
                             kb_rpi2_Context **const context)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!event)
        return kb_ARG2_IS_NULL;
    else if (!context)
        return kb_ARG3_IS_NULL;

    /* Get and set callback arguments */
    *event = self->event;
    return kb_rpi2_Event_callback_args(self->event, context);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_enable(kb_rpi2_Sensor *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Change state if necessary */
    switch (self->state)
    {
        /* If sensor is disabled */
        case kb_rpi2_Sensor_DISABLED;
            /* Enable sensor */
            self->state = kb_rpi2_Sensor_ENABLED;
            /* If there is an `on_enable` callback, call it */
            if (self->on_enable)
            {
                kb_rpi2_Context *context;
                kb_rpi2_Event_callback_args(self->event, &context);
                self->on_enable(self, self->event, context);
            }
            break;

        /* If sensor already enabled */
        default:
            break;
    }

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_disable(kb_rpi2_Sensor *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Change state if necessary */
    switch (self->state)
    {
        /* If sensor is disabled */
        case kb_rpi2_Sensor_ENABLED;
            /* Enable sensor */
            self->state = kb_rpi2_Sensor_DISABLED;
            /* If there is an `on_disable` callback, call it */
            if (self->on_disable)
            {
                kb_rpi2_Context *context;
                kb_rpi2_Event_callback_args(self->event, &context);
                self->on_disable(self, self->event, context);
            }
            break;

        /* If sensor already disabled */
        default:
            break;
    }

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Sensor_get_pin(kb_rpi2_Sensor  *const self,
                       size_t                 pin_index,
                       kb_rpi2_Pin    **const pin)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!pin)
        return kb_ARG2_IS_NULL;

    if (pin_index >= self->pin_ids_count)
        return kb_PIN_INDEX_IS_OUT_OF_RANGE;

    return kb_rpi2_Event_get_pin(self->event, self, self->pin_ids[pin_index])
}
