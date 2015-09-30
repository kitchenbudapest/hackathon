/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        hall    = new kb.rpi2.sensors.HallEffect(event, kb.rpi2.PIN3);

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

    hall.onMagnetize = function ()
    {
        print("Hey, I'm polarized!");
    };

    hall.onDemagnetize = function ()
    {
        print('Where have the magnets gone?');
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
