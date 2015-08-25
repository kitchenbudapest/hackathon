## INFO ##
## INFO ##

# Import kb modules
from kb.RPi2         import Context, Event
from kb.RPi2.sensors import LED, FourKeys

# Create containers
context = Context()
event1  = Event(context)
event2  = Event(context)

@event1
def on_exit(*args, **kwargs):
    print('EXITING (from event1)')

@event2
def on_exit(*args, **kwargs):
    print('EXITING (from event2)')


# Create sensors for event1
led1       = LED(event1)
four_keys1 = FourKeys(event1)

@four_keys1
def on_key_pressed_1(context, event, sensor):
    print('KEY PRESSED: 1')
    print('TURN LED: ON')
    led.on()

@four_keys1
def on_key_pressed_2(context, event, sensor):
    print('KEY PRESSED: 1')
    print('TURN LED: OFF')
    led.off()

@four_keys1
def on_key_pressed_4(context, event, sensor):
    print('KEY PRESSED: 4')
    print('SWITCHING MODE => 2')
    context.switch(event2)


# Create sensors for event2
led2       = LED(event2)
four_keys2 = FourKeys(event2)

@four_keys2
def on_key_pressed_1(context, event, sensor):
    print('KEY PRESSED: 1')
    print('TURN LED: OFF')
    lef.off()

@four_keys2
def on_key_pressed_2(context, event, sensor):
    print('KEY PRESSED: 2')
    print('TURN LED: ON')
    led.on()

@four_keys2
def on_key_pressed_4(context, event, sensor):
    print('KEY PRESSED: 4')
    print('SWITCHING MODE => 1')
    context.switch(event1)
