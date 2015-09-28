/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context  = new kb.rpi2.Context(),
        event    = new kb.rpi2.Event(context),
        led      = new kb.rpi2.sensors.LED(event, kb.rpi2.PIN3),
        fourKeys = new kb.rpi2.sensors.FourKeys(event,
                                                kb.rpi2.PIN37,  // row
                                                kb.rpi2.PIN29,  // col1
                                                kb.rpi2.PIN31,  // col2
                                                kb.rpi2.PIN33,  // col3
                                                kb.rpi2.PIN35); // col4

    var off = function ()
    {
        led.off();
    };

    led.onEnable  = off;
    led.onDisable = off;

    fourKeys.onKey1 = function ()
    {
        print('led => ON');
        led.on();
    };

    fourKeys.onKey2 = function ()
    {
        print('led => OFF');
        led.off();
    };

    fourKeys.onKey3 = function ()
    {
        print('key3 pressed!');
    };

    fourKeys.onKey4 = function (fourKeys, event, context)
    {
        print('event-loop => STOP');
        context.stop();
    };

    print('event-loop => START');
    event.activate();
    context.start();
})();
