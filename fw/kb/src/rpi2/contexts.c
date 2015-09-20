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
            kb_utils_DenseSetIter
            kb_utils_DenseSetItem
    func  : kb_utils_DenseSet_new
            kb_utils_DenseSet_del
            kb_utils_DenseSet_has
            kb_utils_DenseSet_push
            kb_utils_DenseSet_pull
            kb_utils_DenseSetIter_new
            kb_utils_DenseSetIter_del
            kb_utils_DenseSetIter_next */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event
    func  : kb_rpi2_Event_reset_pins
            kb_rpi2_Event_disable_all
            kb_rpi2_Event_listen_all_pins */
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

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

    /* Create new Context object */
    kb_rpi2_Context *context;
    if (!(context = malloc(sizeof(kb_rpi2_Context))))
        return kb_ALLOC_FAIL;

    /* Initialize new Context object */
    kb_Error error;
    if ((error = kb_rpi2_Context_ini(context)))
    {
        free(context);
        return error;
    }

    /* If everything went fine, return values */
    *self = context;
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_ini(kb_rpi2_Context *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Create new DenseSet object */
    if (kb_utils_DenseSet_new(&(self->events), INITIAL_CONTEXT_LIMIT))
        return kb_ALLOC_FAIL;

    /* Set members */
    self->looping        = false;
    self->exiting        = false;
    self->curr_active    = NULL;
    self->next_active    = NULL;
    self->on_start       = NULL;
    self->on_stop        = NULL;
    self->on_cycle_begin = NULL;
    self->on_cycle_end   = NULL;
    self->on_activate    = NULL;
    self->on_exit        = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_fin(kb_rpi2_Context *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Create an iterator to go through all
       Event objects bound to this Context */
    kb_Error error;
    kb_utils_DenseSetIter  iter;
    kb_utils_DenseSetItem *item;
    if ((error = kb_utils_DenseSetIter_ini(&iter, self->events)))
        return error;

    /* Reset all pins used by all Events */
    for (kb_utils_DenseSetIter_next(&iter, &item);
         item;
         kb_utils_DenseSetIter_next(&iter, &item))
            kb_rpi2_Event_reset_all_pins((kb_rpi2_Event *const)item);

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_del(kb_rpi2_Context **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

    /* Finalize instance */
    kb_rpi2_Context_fin(*self);

    /* Deallocate instance and redirect self */
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
    /* If there is no active current event */
    else if (!self->curr_active)
    {
        /* If there is no scheduled active event */
        if (!(self->curr_active = self->next_active))
            return kb_NO_EVENT_ACTIVATED;
        /* If there is scheduled active event */
        else
        {
            /* If there is an `on_activate` callback, call it */
            if (self->on_activate)
                if ((error = self->on_activate(self,
                                               NULL,
                                               self->curr_active)))
                    return error;

            /* Enable all sensors for next event */
            kb_rpi2_Event_enable_all_sensors(self->curr_active);

            /* Clear schedule */
            self->next_active = NULL;
        }
    }

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

        /* Get signals from pins */
        kb_rpi2_Event_listen_all_pins(self->curr_active);

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
            kb_rpi2_Event_reset_all_pins(self->curr_active);

            /* Disable all sensors for current event */
            kb_rpi2_Event_disable_all_sensors(self->curr_active);

            /* Enable all sensors for next event */
            kb_rpi2_Event_enable_all_sensors(self->next_active);

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
#define BIND_FUNCTION(FUNC)                                                    \
    kb_Error                                                                   \
    kb_rpi2_Context_bind_##FUNC(kb_rpi2_Context *const self,                   \
                                kb_Error (*FUNC)(kb_rpi2_Context *const,       \
                                                 kb_rpi2_Event   *const))      \
    {                                                                          \
        /* If any of the arguments is NULL */                                  \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
        else if (!FUNC)                                                        \
            return kb_ARG2_IS_NULL;                                            \
                                                                               \
        /* Set callback */                                                     \
        self->FUNC = FUNC;                                                     \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create binding functions */
BIND_FUNCTION(on_start)
BIND_FUNCTION(on_stop)
BIND_FUNCTION(on_cycle_begin)
BIND_FUNCTION(on_cycle_end)
BIND_FUNCTION(on_exit)


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
#define UNBIND_FUNCTION(FUNC)                                                  \
    kb_Error                                                                   \
    kb_rpi2_Context_unbind_##FUNC(kb_rpi2_Context *const self)                 \
    {                                                                          \
        /* If `self` is NULL */                                                \
        if (!self)                                                             \
            return kb_SELF_IS_NULL;                                            \
                                                                               \
        /* Unset callback */                                                   \
        self->FUNC = NULL;                                                     \
                                                                               \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Create unbinding functions */
UNBIND_FUNCTION(on_start)
UNBIND_FUNCTION(on_stop)
UNBIND_FUNCTION(on_cycle_begin)
UNBIND_FUNCTION(on_cycle_end)
UNBIND_FUNCTION(on_exit)
UNBIND_FUNCTION(on_activate)
