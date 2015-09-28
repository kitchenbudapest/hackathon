/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context   = new kb.rpi2.Context(),
        event1    = new kb.rpi2.Event(context),
        event2    = new kb.rpi2.Event(context),
        led1      = new kb.rpi2.sensors.LED(event1, kb.rpi2.PIN3),
        fourKeys1 = new kb.rpi2.sensors.FourKeys(event1,
                                                kb.rpi2.PIN37,  // row
                                                kb.rpi2.PIN29,  // col1
                                                kb.rpi2.PIN31,  // col2
                                                kb.rpi2.PIN33,  // col3
                                                kb.rpi2.PIN35), // col4
        led2      = new kb.rpi2.sensors.LED(event2, kb.rpi2.PIN3),
        fourKeys2 = new kb.rpi2.sensors.FourKeys(event2,
                                                kb.rpi2.PIN37,  // row
                                                kb.rpi2.PIN29,  // col1
                                                kb.rpi2.PIN31,  // col2
                                                kb.rpi2.PIN33,  // col3
                                                kb.rpi2.PIN35); // col4

    led1.onEnable    =
    led1.onDisable   =
    led2.onEnable    =
    led2.onDisable   = function (led)
    {
        print('led => OFF');
        led.off();
    };

    fourKeys1.onKey2 = function ()
    {
        print('led => OFF');
        led1.off();
    }
    fourKeys2.onKey1 = function ()
    {
        print('led => OFF');
        led2.off();
    };

    fourKeys1.onKey1 = function ()
    {
        print('led => ON');
        led1.on();
    }
    fourKeys2.onKey2 = function ()
    {
        print('led => ON');
        led2.on();
    };

    fourKeys1.onKey4 = function ()
    {
        print('switch event');
        event2.activate();
    };

    fourKeys2.onKey4 = function ()
    {
        print('switch event');
        event1.activate();
    };

    fourKeys1.onKey3 =
    fourKeys2.onKey3 = function (fourKeys, event, context)
    {
        print('event-loop => STOP');
        context.stop();
    };

    print('event-loop => START');
    event1.activate();
    context.start();
})();
