/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_CONTEXTS_H_4121997444361183__
#define __KB_RPI2_CONTEXTS_H_4121997444361183__


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */


/*----------------------------------------------------------------------------*/
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of internals failed */
kb_Error
kb_rpi2_Context_new(kb_rpi2_Context **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Context_del(kb_rpi2_Context **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of internals failed */
kb_Error
kb_rpi2_Context_bind_event(kb_rpi2_Context *const self,
                           kb_rpi2_Event   *const event);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ITEM_NOT_IN_CONTAINER:
        if second argument is not in first argument */
kb_Error
kb_rpi2_Context_unbind_event(kb_rpi2_Context *const self,
                             kb_rpi2_Event   *const event);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_EVENT_NOT_BOUND_TO_CONTEXT:
        if event has not been bound to the given context */
kb_Error
kb_rpi2_Context_activate_event(kb_rpi2_Context *const self,
                               kb_rpi2_Event   *const event);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_NO_EVENT_ACTIVATED:
        if there is no event activated for the given context
    kb_*:
        if any of the callbacks returns user specified error signals */
kb_Error
kb_rpi2_Context_start(kb_rpi2_Context *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Context_stop(kb_rpi2_Context *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Context_exit(kb_rpi2_Context *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_start(kb_rpi2_Context *const self,
                              kb_Error (*on_start)(kb_rpi2_Context *const,
                                                   kb_rpi2_Event   *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_stop(kb_rpi2_Context *const self,
                             kb_Error (*on_stop)(kb_rpi2_Context *const,
                                                 kb_rpi2_Event   *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_cycle_begin(kb_rpi2_Context *const self,
                                    kb_Error (*on_cycle_begin)(kb_rpi2_Context *const,
                                                               kb_rpi2_Event   *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_cycle_end(kb_rpi2_Context *const self,
                                  kb_Error (*on_cycle_end)(kb_rpi2_Context *const,
                                                           kb_rpi2_Event   *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_activate(kb_rpi2_Context *const self,
                                 kb_Error (*on_activate)(kb_rpi2_Context *const,
                                                         kb_rpi2_Event   *const,
                                                         kb_rpi2_Event   *const));
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Context_bind_on_exit(kb_rpi2_Context *const self,
                             kb_Error (*on_exit)(kb_rpi2_Context *const,
                                                 kb_rpi2_Event   *const));

#endif /* __KB_RPI2_CONTEXTS_H_4121997444361183__ */
