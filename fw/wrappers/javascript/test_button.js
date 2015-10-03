/* INFO **
** INFO */

(function ()
{
    'use strict';

    var context = new kb.rpi2.Context();
    var event   = new kb.rpi2.Event(context);
    var button  = new kb.rpi2.sensors.Button(event, kb.rpi2.PIN11);
    var motor1  = new kb.rpi2.sensors.StepMotor(event,
                                                kb.rpi2.PIN31,
                                                kb.rpi2.PIN33,
                                                kb.rpi2.PIN35,
                                                kb.rpi2.PIN37);
    var motor2  = new kb.rpi2.sensors.StepMotor(event,
                                                kb.rpi2.PIN32,
                                                kb.rpi2.PIN36,
                                                kb.rpi2.PIN38,
                                                kb.rpi2.PIN40);

    var state = true;
    button.onPress = function ()
    {
        if (state)
        {
            motor1.rotate(0.33);
            state = false;
        }
        else
        {
            motor2.rotate(0.33);
            state = true;
        }
    }

    event.activate();
    context.start();
})();
