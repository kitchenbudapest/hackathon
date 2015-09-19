## INFO ##
## INFO ##

from kb.rpi2 import (Context,
                     Event,
                     LED,
                     FourKeys,
                     PIN1,
                     PIN2,
                     PIN3,
                     PIN4,
                     PIN5,
                     PIN6)

print('>>> Starting...')

context   = Context()
event     = Event(context)
led       = LED(event, PIN1)
four_keys = FourKeys(event, pin_row  = PIN2,
                            pin_col1 = PIN3,
                            pin_col2 = PIN4,
                            pin_col3 = PIN5,
                            pin_col4 = PIN6)

@event
def on_key_3(for_keys, event, context):
    print('four_keys.on_key_3()')

@event
def on_enable(four_keys, event, context):
    print('four_keys.on_enable()')

@led
def on_on(led, event, context):
    print('led.on_on()')

@context
def on_cycle_begin(context, event):
    print('context.on_cycle_begin()')
    @context
    def on_cycle_end(context, event):
        print('context.on_cycle_end()')
        context.stop()

@context
def on_stop(context, event):
    print('context.on_stop()')

event.activate()
context.start()

print('<<< Exiting...')
