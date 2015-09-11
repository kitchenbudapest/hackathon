/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
#define kb_rpi2_PIN_COUNT 40


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_Context         *context;
    kb_rpi2_Pin     **const  pins[kb_rpi2_PIN_COUNT];
    kb_rpi2_Sensor  **const  sensors;
    size_t                   sensors_count;
    size_t                   sensors_limit;
    size_t                   sensors_index;
} kb_rpi2_Event;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_new(kb_rpi2_Event   *const *self,
                  kb_rpi2_Context *const  context);


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Event_del(kb_rpi2_Event *const *self);

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
