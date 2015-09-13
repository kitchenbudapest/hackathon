/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */
#include <stdbool.h>
/*  type  : bool
    const : true
            false */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ALLOC_FAIL */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet
    func  : kb_utils_DenseSet_new
            kb_utils_DenseSet_del
            kb_utils_DenseSet_push
            kb_utils_DenseSet_pull */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event */


/*----------------------------------------------------------------------------*/
typedef struct
{
    /* Data */
    kb_utils_DenseSet  *events;

    /* States */
    kb_rpi2_Event      *active;
    bool                looping;
    bool                exiting;

    /* Callbacks */
    kb_Error          (*on_start)(kb_rpi2_Context       *const);
    kb_Error          (*on_stop)(kb_rpi2_Context        *const);
    kb_Error          (*on_cycle_begin)(kb_rpi2_Context *const);
    kb_Error          (*on_cycle_end)(kb_rpi2_Context   *const);
    kb_Error          (*on_activate)(kb_rpi2_Context    *const);
    kb_Error          (*on_exit)(kb_rpi2_Context        *const);
} kb_rpi2_Context;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
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
    if (kb_utils_DenseSet_new(&(context->sensors), context))
        goto Sensors_Alloc_Failed;

    /* Set members */
    context->active         = NULL;
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
