/* INFO **
** INFO */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : puts */
#include <stdlib.h>
/*  const : EXIT_SUCCESS
            EXIT_FAILURE */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kib_OKAY */
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


/*----------------------------------------------------------------------------*/
kb_Error
on_cycle_end(kb_rpi2_Context *const context,
             kb_rpi2_Event   *const event)
{
    (void)event;
    puts("Context.on_cycle_end()");
    kb_rpi2_Context_stop(context);
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
on_cycle_begin(kb_rpi2_Context *const context,
               kb_rpi2_Event   *const event)
{
    (void)event;
    puts("Context.on_cycle_begin()");
    kb_rpi2_Context_bind_on_cycle_end(context, on_cycle_end);
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
on_enable(kb_rpi2_sensors_FourKeys *const four_keys,
          kb_rpi2_Event            *const event,
          kb_rpi2_Context          *const context)
{
    (void)four_keys;
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

    /* Create "actors" */
    if (kb_rpi2_Context_new(&context))
    {
        puts("Context.new() allocation failed");
        return EXIT_FAILURE;
    }
    else if (kb_rpi2_Event_new(&event, context))
    {
        puts("Event.new() allocation failed");
        return EXIT_FAILURE;
    }
    else if (kb_rpi2_sensors_LED_new(&led, event))
    {
        puts("LED.new() allocation failed");
        return EXIT_FAILURE;
    }
    else if (kb_rpi2_sensors_FourKeys_new(&four_keys, event))
    {
        puts("FourKeys.new() allocation failed")
        return EXIT_FAILURE;
    }

    /* Bind callbacks */
    kb_rpi2_sensors_FourKeys_bind_on_key_3(four_keys, on_key_3);
    kb_rpi2_Sensor_bind_on_enable((kb_rpi2_Sensor *const)four_keys, on_enable);

    kb_rpi2_sensors_LED_bind_on_on(led, on_on);

    kb_rpi2_Context_bind_on_cycle_begin(context, on_cycle_begin);
    kb_rpi2_Context_bind_on_stop(context, on_stop);

    /* Enter event loop */
    kb_rpi2_Event_activate(event);
    kb_rpi2_Context_start(context);

    /* Clean up */
    kb_rpi2_Event_del(&event);
    kb_rpi2_Context_del(&context);

    /* Should not reach this point */
    puts("Exiting now...");
    return EXIT_SUCCESS;
}
