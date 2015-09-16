/* INFO **
** INFO */

/* Header guards */
#ifndef __KB_RPI2_TYPES_H_7452310872486105__
#define __KB_RPI2_TYPES_H_7452310872486105__

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdbool.h>
/*  type  : bool */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet */
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinState
            kb_rpi2_PinId
            kb_rpi2_SensorState */


/*----------------------------------------------------------------------------*/
/* Forward declarations to avoid circular dependencies */
struct kb_rpi2_context;
struct kb_rpi2_event;
struct kb_rpi2_sensor;
struct kb_rpi2_pin;



/*----------------------------------------------------------------------------*/
#define KB_RPI2_CONTEXT_MEMBERS()                                              \
    /* Data */                                                                 \
    kb_utils_DenseSet  *events;                                                \
    /* States */                                                               \
    struct kb_rpi2_event  *curr_active;                                        \
    struct kb_rpi2_event  *next_active;                                        \
    bool                   looping;                                            \
    bool                   exiting;                                            \
    /* Callbacks */                                                            \
    kb_Error             (*on_start)(struct kb_rpi2_context *const,            \
                                     struct kb_rpi2_event   *const);           \
    kb_Error             (*on_stop)(struct kb_rpi2_context *const,             \
                                    struct kb_rpi2_event   *const);            \
    kb_Error             (*on_cycle_begin)(struct kb_rpi2_context *const,      \
                                           struct kb_rpi2_event   *const);     \
    kb_Error             (*on_cycle_end)(struct kb_rpi2_context *const,        \
                                         struct kb_rpi2_event   *const);       \
    kb_Error             (*on_activate)(struct kb_rpi2_context *const,         \
                                        struct kb_rpi2_event   *const,         \
                                        struct kb_rpi2_event   *const);        \
    kb_Error             (*on_exit)(struct kb_rpi2_context *const,             \
                                    struct kb_rpi2_event   *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_context
{
    KB_RPI2_CONTEXT_MEMBERS()
} kb_rpi2_Context;



/*----------------------------------------------------------------------------*/
#define KB_RPI2_PINS_COUNT (size_t)40
#define KB_RPI2_EVENT_MEMBERS()                                                \
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()                                          \
    struct kb_rpi2_context *context;                                           \
    kb_utils_DenseSet      *sensors;                                           \
    struct kb_rpi2_pin     *pins[KB_RPI2_PINS_COUNT];                          \
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_event
{
    KB_RPI2_EVENT_MEMBERS()
} kb_rpi2_Event;



/*----------------------------------------------------------------------------*/
#define KB_RPI2_SENSOR_MEMBERS()                                               \
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()                                          \
    struct kb_rpi2_event  *event;                                              \
    kb_rpi2_PinId         *pin_ids;                                            \
    size_t                 pin_ids_count;                                      \
    kb_rpi2_SensorState    state;                                              \
    kb_Error             (*on_enable)(struct kb_rpi2_sensor  *const,           \
                                      struct kb_rpi2_event   *const,           \
                                      struct kb_rpi2_context *const);          \
    kb_Error             (*on_disable)(struct kb_rpi2_sensor  *const,          \
                                       struct kb_rpi2_event   *const,          \
                                       struct kb_rpi2_context *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensor
{
    KB_RPI2_SENSOR_MEMBERS()
} kb_rpi2_Sensor;



/*----------------------------------------------------------------------------*/
#define KB_RPI2_PIN_MEMBERS()                                                  \
    /* Static data */                                                          \
    kb_rpi2_PinId           id;                                                \
    kb_rpi2_PinState        state;                                             \
    struct kb_rpi2_sensor  *sensor;                                            \
    /* Available callbacks */                                                  \
    kb_Error              (*on_high)(struct kb_rpi2_pin     *const,            \
                                     struct kb_rpi2_sensor  *const,            \
                                     struct kb_rpi2_event   *const,            \
                                     struct kb_rpi2_context *const);           \
    kb_Error              (*on_low)(struct kb_rpi2_pin     *const,             \
                                    struct kb_rpi2_sensor  *const,             \
                                    struct kb_rpi2_event   *const,             \
                                    struct kb_rpi2_context *const);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_pin
{
    KB_RPI2_PIN_MEMBERS()
} kb_rpi2_Pin;


#endif /* __KB_RPI2_TYPES_H_7452310872486105__ */
