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

    context.onCycleEnd = "hello, world!";

    // context.onCycleEnd = function (c, e)
    // {
    //     print('in onCycleEnd, context =', c);
    //     print('in onCycleEnd, event =', e);
    //     c.stop();
    // };

    print(context);
    print(Object.keys(context));

    event1.activate();
    context.start();
})();
