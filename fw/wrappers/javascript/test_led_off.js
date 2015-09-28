/* INFO **
** INFO */

(function ()
{
    'use strict';

    /* Turn OFF the LED at PIN3 */
    (new kb.rpi2.sensors.LED(new kb.rpi2.Event(new kb.rpi2.Context()),
                             kb.rpi2.PIN3)).off();
})();
