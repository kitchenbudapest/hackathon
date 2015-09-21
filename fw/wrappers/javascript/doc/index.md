`kbjs`
======

Basic "hello, world" application:

```js
(function ()
{
    'use strict';

    var context = new kb.rpi2.Context(),
        event   = new kb.rpi2.Event(context);

    context.onStart = function ()
    {
        print('hello,');
        context.stop();
    };

    context.onStop = function ()
    {
        print('world!');
    };

    event.activate();
    context.start();
})();
```


`kb.rpi2.Context`
-----------------

Event loop:

1. Start (called only once)
2. CycleBegin (called everytime a new cycle begins)
3. Event/Sensor/Pin callbacks called
4. CycleEnd (called everytime a cycle ends)
5. Activate (called everytime an event is activated)
6. Stop (called only once)
7. Exit (called only once)



Methods:

- *constructor*`()`: `Context` must be called as a constructor (via the `new`
  keyword), otherwise an error will be thrown.
  Example:
  ```js
  var context = new kb.rpi2.Context();
  ```

- **`start()`**: Enter event loop. This method will only return if `stop()` or
  `exit()` called inside the loop, or a user error returned. The loop will start
  only if there is an `Event` bound to this Context is actived, otherwise this
  method will throw an error.
  Example:
  ```js
  event.activate();
  context.start();
  ```

- **`stop()`**: As all direct method calls, it is not guaranteed that it has
  immediate effect, it will be called at the proper stage of the cycle of the
  event loop.
  Example:
  ```js
  context.stop();
  ```

- **`exit()`**: As all direct method calls, it is not guaranteed that it has
  immediate effect, it will be called at the proper stage of the cycle of the
  event loop.
  >**WARNING:** Do not use this method, unless you have a very good reason to do
  > so. This method will terminate your program no matter what, and it won't
  > clean up after itself. However, this danger will be changed in the future,
  > when the asynchronous API gets stabilazed.
  Example:
  ```js
  context.exit();
  ```



Callbacks:

Callbacks can be set by assigning a callable to one of the following properties
of Context. Example:

```js
var context = kb.rpi2.Context();
context.onStart = function ()
{
    print('This line is printed from context.onStart!');
};
```

If any of the callbacks returns a value, the boolean value of which is `true`,
the loop will stop.

- **`onStart(context: Context, event: Event)`**: ...
- **`onStop(context: Context, event: Event)`**: ...
- **`onCycleBegin(context: Context, event: Event)`**: ...
- **`onCycleEnd(context: Context, event: Event)`**: ...
- **`onActivate(context: Context, current: Event, next: Event)`**: called right
  before an Event activation is completed. The `current` argument holds the
  Event which will be deactivated, and the `next` argument holds the Event
  which will be activated.
  > **WARNING:** The `current` argument can be `undefined`, so always check for
  > its value, before you get or set or call a property on it. This will only
  > happen for the first time an Event is activated on the context.
