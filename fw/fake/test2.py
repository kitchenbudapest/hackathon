## INFO ##
## INFO ##

# Import kb modules
from kb.RPi2         import Context, Event
from kb.RPi2.sensors import LED, FourKeys

# Create containers
context = Context()
event1  = Event(context)
event2  = Event(context)


# Create exit signals
@event1
def on_exit(*args, **kwargs):
    print('EXITING (from event1)')

@event2
def on_exit(*args, **kwargs):
    print('EXITING (from event2)')


# Use variables to store pins in use
led_pin        = 1
four_keys_pins = {'pin_row'  : 2,
                  'pin_col1' : 3,
                  'pin_col2' : 4,
                  'pin_col3' : 5,
                  'pin_col4' : 6}

# Create sensors
led1       = LED(event1, led_pin)
led2       = LED(event2, led_pin)
four_keys1 = FourKeys(event1, **four_keys_pins)
four_keys2 = FourKeys(event2, **four_keys_pins)


# Key press events when `event1` is active
@four_keys1
def on_key_pressed_1(context, event, sensor):
    print('KEY PRESSED: 1 => TURN LED: ON')
    led1.on()

@four_keys1
def on_key_pressed_2(context, event, sensor):
    print('KEY PRESSED: 2 => TURN LED: OFF')
    led1.off()

@four_keys1
def on_key_pressed_3(context, event, sensor):
    print('KEY PRESSED: 3 => SWITCHING MODE: event2')
    context.switch(event2)


# Key press events when `event2` is active
@four_keys2
def on_key_pressed_1(context, event, sensor):
    print('KEY PRESSED: 1 => TURN LED: OFF')
    led2.off()

@four_keys2
def on_key_pressed_2(context, event, sensor):
    print('KEY PRESSED: 2 => TURN LED: ON')
    led2.on()

@four_keys2
def on_key_pressed_3(context, event, sensor):
    print('KEY PRESSED: 3 => SWITCHING MODE: event1')
    context.switch(event1)


# Key press events either `event1` or `event2` active
@four_keys1
@four_keys2
def on_key_pressed_4(context, event, sensor):
    print('KEY PRESSED: 4 => EXITING...')
    context.exit()


# Start event loop
print('STARTING (from event1)')
context.switch(event1)
context.start()
