/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        led     = new kb.rpi2.sensors.LED(event, kb.rpi2.PIN3);

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
