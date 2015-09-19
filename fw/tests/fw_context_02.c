/* INFO **
** INFO */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : fputs
            puts
    const : stdout */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE
    func  : exit */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
    func  : kb_Error_str */
#define KB_ERROR_TESTING 1
#include <kb/utils/error_testing.h>
/*  macro : KB_ERROR_TRY */
#include <kb/rpi2/enums.h>
/*  const : kb_rpi2_PIN1
            kb_rpi2_PIN2
            kb_rpi2_PIN3
            kb_rpi2_PIN4
            kb_rpi2_PIN5
            kb_rpi2_PIN6 */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  : kb_rpi2_Context_new
            kb_rpi2_Context_del
            kb_rpi2_Context_bind_on_cycle_begin
            kb_rpi2_Context_bind_on_cycle_end
            kb_rpi2_Context_bind_on_exit
            kb_rpi2_Context_start
            kb_rpi2_Context_stop */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event
    func  : kb_rpi2_Event_new
            kb_rpi2_Event_del
            kb_rpi2_Event_activate */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    func  : kb_rpi2_Sensor_bind_on_enable */
#include <kb/rpi2/sensors/leds.h>
/*  type  : kb_rpi2_sensors_LED
            kb_rpi2_sensors_LED_new
            kb_rpi2_sensors_LED_del
            kb_rpi2_sensors_LED_bind_on_on */
#include <kb/rpi2/sensors/four_keys.h>
/*  type  : kb_rpi2_sensors_FourKeys
    func  : kb_rpi2_sensors_FourKeys_new
            kb_rpi2_sensors_FourKeys_del
            kb_rpi2_sensors_FourKeys_bind_on_key_4 */


/*----------------------------------------------------------------------------*/
kb_Error
on_cycle_end(kb_rpi2_Context *const context,
             kb_rpi2_Event   *const event)
{
    (void)event;
    puts("Context.on_cycle_end()");
    KB_ERROR_TRY(kb_rpi2_Context_stop(context));
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_cycle_begin(kb_rpi2_Context *const context,
               kb_rpi2_Event   *const event)
{
    (void)event;
    puts("Context.on_cycle_begin()");
    KB_ERROR_TRY(kb_rpi2_Context_bind_on_cycle_end(context, on_cycle_end));
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_stop(kb_rpi2_Context *const context,
        kb_rpi2_Event   *const event)
{
    (void)context;
    (void)event;
    puts("Context.on_stop()");
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_enable(kb_rpi2_Sensor  *const sensor,
          kb_rpi2_Event   *const event,
          kb_rpi2_Context *const context)
{
    (void)sensor;
    (void)event;
    (void)context;
    puts("FourKeys.on_enable()");
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_key_3(kb_rpi2_sensors_FourKeys *const four_keys,
         kb_rpi2_Event            *const event,
         kb_rpi2_Context          *const context)
{
    (void)four_keys;
    (void)event;
    (void)context;
    puts("FourKeys.on_key_3()");
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_on(kb_rpi2_sensors_LED *const led,
      kb_rpi2_Event       *const event,
      kb_rpi2_Context     *const context)
{
    (void)led;
    (void)event;
    (void)context;
    puts("LED.on_on()");
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
int
main(void)
{
    kb_rpi2_Context          *context;
    kb_rpi2_Event            *event;
    kb_rpi2_sensors_LED      *led;
    kb_rpi2_sensors_FourKeys *four_keys;

    puts(">>> Starting...");

    /* Create "actors" */
    KB_ERROR_TRY(kb_rpi2_Context_new(&context));
    KB_ERROR_TRY(kb_rpi2_Event_new(&event, context));
    KB_ERROR_TRY(kb_rpi2_sensors_LED_new(&led, event, kb_rpi2_PIN1));
    KB_ERROR_TRY(kb_rpi2_sensors_FourKeys_new(&four_keys,
                                              event,
                                              kb_rpi2_PIN2,
                                              kb_rpi2_PIN3,
                                              kb_rpi2_PIN4,
                                              kb_rpi2_PIN5,
                                              kb_rpi2_PIN6));

    /* Bind callbacks */
    KB_ERROR_TRY(kb_rpi2_sensors_FourKeys_bind_on_key_3(four_keys, on_key_3));
    KB_ERROR_TRY(kb_rpi2_Sensor_bind_on_enable((kb_rpi2_Sensor *const)four_keys,
                                               on_enable));

    KB_ERROR_TRY(kb_rpi2_sensors_LED_bind_on_on(led, on_on));

    KB_ERROR_TRY(kb_rpi2_Context_bind_on_cycle_begin(context, on_cycle_begin));
    KB_ERROR_TRY(kb_rpi2_Context_bind_on_stop(context, on_stop));

    /* Enter event loop */
    KB_ERROR_TRY(kb_rpi2_Event_activate(event));
    KB_ERROR_TRY(kb_rpi2_Context_start(context));

    /* Clean up */
    KB_ERROR_TRY(kb_rpi2_sensors_LED_del(&led));
    KB_ERROR_TRY(kb_rpi2_sensors_FourKeys_del(&four_keys));
    KB_ERROR_TRY(kb_rpi2_Event_del(&event));
    KB_ERROR_TRY(kb_rpi2_Context_del(&context));

    /* Should not reach this point */
    puts("<<< Exiting...");
    return EXIT_SUCCESS;
}
