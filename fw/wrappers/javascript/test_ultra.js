/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        ultra   = new kb.rpi2.sensors.UltrasonicSensor(event,
                                                       kb.rpi2.PIN3,
                                                       kb.rpi2.PIN5);

    var counter  = 0;
    context.onCycleEnd = function ()
    {
        print('Distance:', ultra.measure());
        if (counter++ >= 300)
        {
            print('End looping...');
            context.stop();
        }
        sleep(150);
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
