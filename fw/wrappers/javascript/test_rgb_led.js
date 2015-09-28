/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context),
        rgbLed  = new kb.rpi2.sensors.RGBLED(event,
                                             kb.rpi2.PIN13,   // red
                                             kb.rpi2.PIN12,   // green
                                             kb.rpi2.PIN11);  // blue

    var cycles_counter = 0,
        colors_counter = 0;

    var colors =
    [
        'red',
        'green',
        'blue',
        'yellow',
        'magenta',
        'cyan',
        'white',
        'black',
    ];

    context.onCycleBegin = function ()
    {
        if (colors_counter >= colors.length)
        {
            colors_counter = 0;
            if (cycles_counter >= 2)
            {
                print('End looping...');
                context.stop();
                return;
            }
            ++cycles_counter;
        }

        print('led is:', colors[colors_counter]);
        rgbLed[colors[colors_counter]]();
        sleep(300);
        ++colors_counter;
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
