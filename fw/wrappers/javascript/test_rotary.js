/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        led     = new kb.rpi2.sensors.LED(event, kb.rpi2.PIN3),
        rotary  = new kb.rpi2.sensors.RotaryEncoder(event,
                                                    kb.rpi2.PIN11,   // switch
                                                    kb.rpi2.PIN12,   // data
                                                    kb.rpi2.PIN13);  // clock

    rotary.onClick = function ()
    {
        print('End looping...');
        context.stop();
    };

    rotary.onRotateClockWise = function ()
    {
        print('Rotated: -->');
    };

    rotary.onRotateCounterClockWise = function ()
    {
        print('Rotated: <--');
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
