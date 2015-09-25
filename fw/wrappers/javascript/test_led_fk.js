/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context  = new kb.rpi2.Context(),
        event    = new kb.rpi2.Event(context),
        led      = new kb.rpi2.sensors.LED(event, kb.rpi2.PIN3),
        fourKeys = new kb.rpi2.sensors.FourKeys(event,
                                                {pinRow  : kb.rpi2.PIN37,
                                                 pinCol1 : kb.rpi2.PIN29,
                                                 pinCol2 : kb.rpi2.PIN31,
                                                 pinCol3 : kb.rpi2.PIN33,
                                                 pinCol4 : kb.rpi2.PIN35});

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
    }

    fourKeys.onKey2 = function ()
    {
        print('led => OFF');
        led.off();
    };

    fourKeys.onKey4 = function (context)
    {
        print('event-loop => STOP');
        context.stop();
    }

    print('event-loop => START');
    event.activate();
    context.start();
})();
