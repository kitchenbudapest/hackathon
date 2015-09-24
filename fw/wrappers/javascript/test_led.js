/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context,
        event,
        led,
        Context = kb.rpi2.Context,
        Event   = kb.rpi2.Event,
        LED     = kb.rpi2.sensors.LED,
        PIN3    = kb.rpi2.PIN3;

    context = new Context();
    event   = new Event(context);
    led     = new LED(event, PIN3);

    var counter = 0;

    context.onCycleBegin = function ()
    {
        print(counter++);
        print("led.on()");
        led.on();
        sleep(1000);
    };

    context.onCycleEnd = function (context, event)
    {
        print("led.off()");
        led.off();
        sleep(1000);
        if (counter >= 10)
            context.stop();
    };

    event.activate();
    context.start();
})();
