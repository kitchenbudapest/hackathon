/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_RPI2_EVENTS_H_6909342993482931__
#define __KB_RPI2_EVENTS_H_6909342993482931__

/* Include kibu headers */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet
    macro : KB_UTILS_DENSE_SET_ITEM_MEMBERS */


/*----------------------------------------------------------------------------*/
#define KB_RPI2_PIN_COUNT 40


/*----------------------------------------------------------------------------*/
#define KB_RPI2_EVENT_MEMBERS()                                                \
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()                                          \
    kb_rpi2_Context    *context;                                               \
    kb_rpi2_Pin       **pins[KB_RPI2_PIN_COUNT];                               \
    kb_utils_DenseSet  *sensors;


/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_RPI2_EVENT_MEMBERS()
} kb_rpi2_Event;


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
kb_rpi2_Event_new(kb_rpi2_Event   **const self,
                  kb_rpi2_Context  *const context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Event_del(kb_rpi2_Event **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_INVALID_PIN_ID:
        if pin_id is out of range
    kb_ARG3_IS_NULL:
        if sensor is a NULL pointer
    kb_SENSOR_IS_NOT_IN_EVENT:
        if sensor is not bound to event
    kb_PIN_ALREADY_USED:
        if pin_id already used in this event
    kb_ALLOC_FAIL:
        if allocation of the new Pin object failed */
kb_Error
kb_rpi2_Event_use_pin(kb_rpi2_Event  *const self,
                      kb_rpi2_PinId         pin_id,
                      kb_rpi2_Sensor *const sensor);

#endif /* __KB_RPI2_EVENTS_H_6909342993482931__ */
