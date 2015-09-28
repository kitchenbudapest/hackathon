/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context   = new kb.rpi2.Context(),
        event     = new kb.rpi2.Event(context),
        stepMotor = new kb.rpi2.sensors.StepMotor(event,
                                                  kb.rpi2.PIN21,   // IN1
                                                  kb.rpi2.PIN22,   // IN2
                                                  kb.rpi2.PIN23,   // IN3
                                                  kb.rpi2.PIN24);  // IN4

    var interval = 150,
        counter  = 0;

    context.onCycleBegin = function ()
    {
        if (counter >= 8)
        {
            print('End looping...');
            context.stop()
        }
        ++counter;
        stepMotor.rotateDegree(45);
        sleep(interval);
    };

    context.onCycleEnd = function ()
    {
        if (counter%2)
        {
            stepMotor.rotateRadian(-0.78539816);
            sleep(interval);
        }
    };

    context.onStop = function ()
    {
        stepMotor.rotate(0.5);
    };

    print('Start looping...');
    event.activate();
    context.start();
})();
