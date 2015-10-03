(function ()
{
    'use strict';

    var context      = new kb.rpi2.Context();
    var controlLed   = new kb.rpi2.Event(context);
    var controlStep  = new kb.rpi2.Event(context);
    var modeLed1Led  = new kb.rpi2.sensors.LED(controlLed, kb.rpi2.PIN3);
    var modeLed1Step = new kb.rpi2.sensors.LED(controlStep, kb.rpi2.PIN3);
    var modeLed2Led  = new kb.rpi2.sensors.LED(controlLed, kb.rpi2.PIN5);
    var modeLed2Step = new kb.rpi2.sensors.LED(controlStep, kb.rpi2.PIN5);
    var keyboard1    = new kb.rpi2.sensors.FourKeys(controlLed,
                                                   kb.rpi2.PIN12,
                                                   kb.rpi2.PIN16,
                                                   kb.rpi2.PIN18,
                                                   kb.rpi2.PIN13,
                                                   kb.rpi2.PIN15);
    var keyboard2    = new kb.rpi2.sensors.FourKeys(controlStep,
                                                    kb.rpi2.PIN12,
                                                    kb.rpi2.PIN16,
                                                    kb.rpi2.PIN18,
                                                    kb.rpi2.PIN13,
                                                    kb.rpi2.PIN15);
    var led          = new kb.rpi2.sensors.LED(controlLed, kb.rpi2.PIN11);
    var motor        = new kb.rpi2.sensors.StepMotor(controlStep,
                                                     kb.rpi2.PIN31,
                                                     kb.rpi2.PIN33,
                                                     kb.rpi2.PIN35,
                                                     kb.rpi2.PIN37);

    var state = true;
    context.onActivate = function (context, event1, event2)
    {

        if (state)
        {
            modeLed1Led.on();
            modeLed2Led.off();
            state = false;
        }
        else
        {
            modeLed1Step.off();
            modeLed2Step.on();
            state = true;
        }
    };

    keyboard1.onKey1 = function ()
    {
        led.on();
    };

    keyboard1.onKey2 = function ()
    {
        led.off();
    };

    keyboard1.onKey3 = function ()
    {
        for (var i=0; i<3; i++)
        {
            led.on();
            sleep(100);
            led.off();
            sleep(100);
        }
    };

    keyboard1.onKey4 = function ()
    {
        controlStep.activate();
    };

    keyboard2.onKey1 = function ()
    {
        motor.rotateDegree(120);
    };

    keyboard2.onKey2 = function ()
    {
        motor.rotateDegree(-120);
    };

    keyboard2.onKey3 = function ()
    {
        context.stop();
    };

    keyboard2.onKey4 = function ()
    {
        controlLed.activate();
    };

    controlLed.activate();
    context.start();
})();
