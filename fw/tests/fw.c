/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  const : EXIT_SUCCESS */


/*----------------------------------------------------------------------------*/
static kb_rpi2_Context         *context;
static kb_rpi2_Event           *event1;
static kb_rpi2_Sensor_LED      *led1;
static kb_rpi2_Sensor_FourKeys *keys1;


/*----------------------------------------------------------------------------*/
kb_Error
keys1_on_keypressed_1(kb_rpi2_Sensor_FourKeys *const self,
                      kb_rpi2_Event           *const event,
                      kb_rpi2_Context         *const context)
{
    kb_rpi2_Sensor_LED_on(led1);
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
keys2_on_keypressed_2(kb_rpi2_Sensor_FourKeys *const self,
                      kb_rpi2_Event           *const event,
                      kb_rpi2_Context         *const context)
{
    kb_rpi2_Sensor_LED_off(led1);
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
keys2_on_keypressed_3(kb_rpi2_Sensor_FourKeys *const self,
                      kb_rpi2_Event           *const event,
                      kb_rpi2_Context         *const context)
{
    kb_rpi2_Context_stop(context);
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
int
main(void)
{
    /* Create context object */
    kb_rpi2_Context_new(&context);

    /* Create first event */
    kb_rpi2_Event_new(&event1, context);
    kb_rpi2_Sensor_LED_new(&led1,
                           event1,
                           kb_rpi2_PIN1);
    kb_rpi2_Sensor_FourKeys_new(&keys1,
                                event1,
                                kb_rpi2_PIN2,
                                kb_rpi2_PIN3,
                                kb_rpi2_PIN4,
                                kb_rpi2_PIN5,
                                kb_rpi2_PIN6);

    /* Set callbacks */
    kb_rpi2_Sensor_FourKeys_bind_on_key_pressed_1(keys1, keys1_on_keypressed_1);
    kb_rpi2_Sensor_FourKeys_bind_on_key_pressed_2(keys1, keys1_on_keypressed_2);
    kb_rpi2_Sensor_FourKeys_bind_on_key_pressed_3(keys1, keys1_on_keypressed_3);

    /* Enter event loop */
    kb_rpi2_Event_activate(event1);
    kb_rpi2_Context_start(context);

    /* Clean up */
    kb_rpi2_Sensor_FourKeys_del(&keys1);
    kb_rpi2_Sensor_LED_del(&led1);
    kb_rpi2_Event_del(&event1);
    kb_rpi2_Context_del(&context);
    return EXIT_SUCCESS;
}
