/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free
            exit
    const : EXIT_SUCCESS */
#include <stdbool.h>
/*  type  : bool
    const : true
            false */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ALLOC_FAIL
            kb_NO_EVENT_ACTIVATED
            kb_EVENT_NOT_BOUND_TO_CONTEXT */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet
    func  : kb_utils_DenseSet_new
            kb_utils_DenseSet_del
            kb_utils_DenseSet_has
            kb_utils_DenseSet_push
            kb_utils_DenseSet_pull */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event
    func  : kb_rpi2_Event_reset_pins
            kb_rpi2_Event_disable_all */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context */


/*----------------------------------------------------------------------------*/
#define INITIAL_CONTEXT_LIMIT (size_t)32


/*----------------------------------------------------------------------------*/
kb_Error
kb_rpi2_Context_new(kb_rpi2_Context **const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Create new Context object */
    kb_rpi2_Context *context;
    if (!(context = malloc(sizeof(kb_rpi2_Context))))
        goto Self_Alloc_Failed;

    /* Create new DenseSet object */
    if (kb_utils_DenseSet_new(&(context->events), INITIAL_CONTEXT_LIMIT))
        goto Sensors_Alloc_Failed;

    /* Set members */
    context->curr_active    = NULL;
    context->next_active    = NULL;
    context->looping        = false;
    context->exiting        = false;
    context->on_start       = NULL;
    context->on_stop        = NULL;
    context->on_cycle_begin = NULL;
    context->on_cycle_end   = NULL;
    context->on_activate    = NULL;
    context->on_exit        = NULL;

    /* If everything went fine */
    return kb_OKAY;

    /* If there was a problem */
    Sensors_Alloc_Failed:
        free(context);
    Self_Alloc_Failed:
        *self = NULL;
        return kb_ALLOC_FAIL;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_del(kb_rpi2_Context **const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Delete DenseSet object */
    kb_utils_DenseSet_del(&(*self)->events);

    /* Delete Context object */
    free(*self);
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_event(kb_rpi2_Context *const self,
                           kb_rpi2_Event   *const event)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Propagate other errors */
    return kb_utils_DenseSet_push(self->events,
                                  (kb_utils_DenseSetItem *const)event);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_unbind_event(kb_rpi2_Context *const self,
                             kb_rpi2_Event   *const event)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Propagate other errors */
    return kb_utils_DenseSet_pull(self->events,
                                  (kb_utils_DenseSetItem *const)event);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_activate_event(kb_rpi2_Context *const self,
                               kb_rpi2_Event   *const event)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Check if event is bound to this context */
    kb_Error error;
    bool     has_event;
    if ((error = kb_utils_DenseSet_has(self->events,
                                       (kb_utils_DenseSetItem *const)event,
                                       &has_event)))
        return error;
    else if (!has_event)
        return kb_EVENT_NOT_BOUND_TO_CONTEXT;

    /* Activate event */
    self->next_active = event;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_start(kb_rpi2_Context *const self)
{
    kb_Error error;

    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    /* If there is no active event */
    else if (!self->curr_active)
        return kb_NO_EVENT_ACTIVATED;

    /* If there is an `on_start` callback, call it */
    if (self->on_start)
        if ((error = self->on_start(self, self->curr_active)))
            return error;

    /* Start looping */
    self->looping = true;

    /* Enter main loop */
    while (self->looping)
    {
        /* If there is an `on_cycle_begin` callback, call it */
        if (self->on_cycle_begin)
            if ((error = self->on_cycle_begin(self, self->curr_active)))
                return error;

        /*
         * TODO: for pin in events: if pin.signaled: pin.on_signal()
         */

        /* If there is an `on_cycle_end` callback, call it */
        if (self->on_cycle_end)
            if ((error = self->on_cycle_end(self, self->curr_active)))
                return error;

        /* If event-activation has been scheduled */
        if (self->next_active)
        {
            /* If there is an `on_activate` callback, call it */
            if (self->on_activate)
                if ((error = self->on_activate(self,
                                               self->curr_active,
                                               self->next_active)))
                    return error;

            /* Reset all pins for current event */
            kb_rpi2_Event_reset_pins(self->curr_active);

            /* Disable all sensors for current event */
            kb_rpi2_Event_disable_all(self->curr_active);

            /* Actiavte next event, clear schedule */
            self->curr_active = self->next_active;
            self->next_active = NULL;
        }
    }

    /* If there is an `on_stop` callback, call it */
    if (self->on_stop)
        if ((error = self->on_stop(self, self->curr_active)))
            return error;

    /* If program should exit */
    if (self->exiting)
    {
        /* there is an `on_exit` callback, call it */
        if (self->on_exit)
            if ((error = self->on_exit(self, self->curr_active)))
                return error;

        /*
         * TODO: reset all pins and clean up!
         */

        /* Terminate program */
        exit(EXIT_SUCCESS);
    }

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_stop(kb_rpi2_Context *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Stop after the current cycle */
    self->looping = false;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_exit(kb_rpi2_Context *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Stop after the current cycle */
    self->looping = false;
    self->exiting = true;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_start(kb_rpi2_Context *const self,
                              kb_Error (*on_start)(kb_rpi2_Context *const,
                                                   kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_start)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_start = on_start;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_stop(kb_rpi2_Context *const self,
                             kb_Error (*on_stop)(kb_rpi2_Context *const,
                                                 kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_stop)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_stop = on_stop;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_cycle_begin(kb_rpi2_Context *const self,
                                    kb_Error (*on_cycle_begin)(kb_rpi2_Context *const,
                                                               kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_cycle_begin)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_cycle_begin = on_cycle_begin;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_cycle_end(kb_rpi2_Context *const self,
                                  kb_Error (*on_cycle_end)(kb_rpi2_Context *const,
                                                           kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_cycle_end)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_cycle_end = on_cycle_end;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_activate(kb_rpi2_Context *const self,
                                 kb_Error (*on_activate)(kb_rpi2_Context *const,
                                                         kb_rpi2_Event   *const,
                                                         kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_activate)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_activate = on_activate;

    /* If everything went fine */
    return kb_OKAY;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_bind_on_exit(kb_rpi2_Context *const self,
                             kb_Error (*on_exit)(kb_rpi2_Context *const,
                                                 kb_rpi2_Event   *const))
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!on_exit)
        return kb_ARG2_IS_NULL;

    /* Set callback */
    self->on_exit = on_exit;

    /* If everything went fine */
    return kb_OKAY;
}
