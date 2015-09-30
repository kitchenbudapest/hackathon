/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        motion  = new kb.rpi2.sensors.MotionSensor(event, kb.rpi2.PIN11);

    motion.onMotion = function ()
    {
        print('Everything is happening so fast!');
    };

    motion.onStill = function ()
    {
        print('Did somebody pause life?');
    };

    var counter  = 0;
    context.onCycleEnd = function ()
    {
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
