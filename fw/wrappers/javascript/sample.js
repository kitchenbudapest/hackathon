/* INFO **
** INFO */

(function ()
{
    'use strict';

    print('>>> Starting...');

    /* Create "actors" */
    var context  = new kb.rpi2.Context(),
        event    = new kb.rpi2.Event(context),
        led      = new kb.rpi2.LED(event, kb.rpi2.PIN1),
        fourKeys = new kb.rpi2.FourKeys(event, {pinRow  : kb.rpi2.PIN2,
                                                pinCol1 : kb.rpi2.PIN3,
                                                pinCol2 : kb.rpi2.PIN4,
                                                pinCol3 : kb.rpi2.PIN5,
                                                pinCol4 : kb.rpi2.PIN6});

    /* Bind callbacks */
    fourKeys.onKey3 = function (fourKeys, event, context)
    {
        print('fourKeys.onKey3()');
    };
    fourKeys.onEnable = function (fourKeys, event, context)
    {
        print('fourKeys.onEnable()');
    };

    led.onOn = function (led, event, context)
    {
        print('led.onOn()');
    };

    context.onCycleBegin = function (context, event)
    {
        print('context.onCycleBegin()');
        context.onCycleEnd = function (context, event)
        {
            print('context.onCycleEnd()');
            context.stop();
        };
    };
    context.onStop = function (context, event)
    {
        print('context.onStop()');
    };

    /* Enter event loop */
    event.activate();
    context.start();

    print('<<< Exiting...');
})();
