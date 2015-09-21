/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context,
        event1,
        event2,
        Context = kb.rpi2.Context,
        Event   = kb.rpi2.Event;

    context = new Context();

    event1  = new Event(context);
    event2  = new Event(context);

    event1.name = 'event1';
    event2.name = 'event2';

    context.onCycleBegin = function ()
    {
        print('in onCycleBegin');

        event2.activate();

        context.onCycleEnd = function (context, event)
        {
            print('in onCycleEnd, context =', context);
            print('in onCycleEnd, event =', event);
            context.stop();
        };
    };

    context.onStop = function ()
    {
        print('in onStop');
    };

    context.onActivate = function (context, curr_event, next_event)
    {
        print('in onActivate');
        print(curr_event ? curr_event.name : undefined);
        print(next_event.name);
    };

    print(Object.keys(context));
    print(context.onActivate);

    event1.activate();
    context.start();

    context.onActivate = "hello";
})();
