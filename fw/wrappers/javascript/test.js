/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context,
        event1,
        event2,
        led1,
        led2,
        Context = kb.rpi2.Context,
        Event   = kb.rpi2.Event,
        LED     = kb.rpi2.sensors.LED,
        PIN3    = kb.rpi2.PIN3;

    context = new Context();

    event1  = new Event(context);
    event2  = new Event(context);

    event1.name = 'event1';
    event2.name = 'event2';

    led1 = new LED(event1, PIN3);
    led2 = new LED(event2, PIN3);

    led1.name = 'led1';
    led2.name = 'led2';

    context.onCycleBegin = function ()
    {
        print('inside: onCycleBegin');
        event2.activate();

        context.onCycleEnd = function (context, event)
        {
            print('inside: onCycleEnd, context =', context);
            print('inside: onCycleEnd, event =', event);
            context.stop();
        };
    };

    context.onStop = function ()
    {
        print('inside: onStop');
    };

    context.onActivate = function (context, curr_event, next_event)
    {
        print('inside: onActivate');
        print('curr:', curr_event ? curr_event.name : undefined);
        print('next:', next_event.name);
    };

    led1.onEnable = function ()
    {
        print('inside: onEnable');
        print('led:', led1.name);
        led1.on();

        print('sleeping start...');
        sleep(1000);
        print('sleep is over!');
    }

    led2.onEnable = function ()
    {
        print('inside: onEnable');
        print('led:', led2.name);
        led2.off();
    }

    event1.activate();
    context.start();
})();
