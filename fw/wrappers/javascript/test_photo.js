/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        photo   = new kb.rpi2.sensors.PhotoResistor(event, kb.rpi2.PIN3);

    photo.onLight = function ()
    {
        print('There is light!');
    };

    photo.onDark = function ()
    {
        print('Darkness, it is...');
    };

    var counter  = 0;
    context.onCycleBegin = function ()
    {
        if (counter++ >= 300)
        {
            print('End looping...');
            context.stop();
        }
        sleep(100);
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
