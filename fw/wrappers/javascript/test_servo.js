/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context    = new kb.rpi2.Context(),
        event      = new kb.rpi2.Event(context),
        servoMotor = new kb.rpi2.sensors.ServoMotor(event, kb.rpi2.PIN3);

    context.onCycleBegin = function ()
    {
        servoMotor.rotateDegree(45);
        sleep(500);
    };

    context.onCycleEnd = function ()
    {
        servoMotor.rotateRadian(-0.78539816);
        sleep(500);
    };

    event.activate();
    context.start();
})();
