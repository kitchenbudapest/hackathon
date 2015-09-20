/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_EVENTS_H_6909342993482931
#define KB_RPI2_EVENTS_H_6909342993482931 1


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet
    macro : KB_UTILS_DENSE_SET_ITEM_MEMBERS */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Context
            kb_rpi2_Event */


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
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of internals failed */
kb_Error
kb_rpi2_Event_ini(kb_rpi2_Event   *const self,
                  kb_rpi2_Context *const context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_rpi2_Event_fin(kb_rpi2_Event *const self);
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
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_rpi2_Event_callback_args(kb_rpi2_Event    *const self,
                            kb_rpi2_Context **const context);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_EVENT_NOT_BOUND_TO_CONTEXT:
        if event has not been bound to the given context */
kb_Error
kb_rpi2_Event_activate(kb_rpi2_Event *const self);
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
kb_rpi2_Event_use_pin(kb_rpi2_Event    *const self,
                      kb_rpi2_PinId           pin_id,
                      kb_rpi2_PinRole         pin_role,
                      kb_rpi2_PinState        pin_state,
                      kb_rpi2_Sensor   *const sensor);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_drop_pin(kb_rpi2_Event *const self,
                       kb_rpi2_PinId        pin_id);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_get_pin(kb_rpi2_Event  *const self,
                      kb_rpi2_PinId         pin_id,
                      kb_rpi2_Pin   **const pin);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_listen_all_pins(kb_rpi2_Event *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_reset_all_pins(kb_rpi2_Event *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_bind_sensor(kb_rpi2_Event  *const self,
                          kb_rpi2_Sensor *const sensor);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_unbind_sensor(kb_rpi2_Event  *const self,
                            kb_rpi2_Sensor *const sensor);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_enable_all_sensors(kb_rpi2_Event *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_disable_all_sensors(kb_rpi2_Event *const self);


#endif /* KB_RPI2_EVENTS_H_6909342993482931 */
