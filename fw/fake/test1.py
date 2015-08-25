## INFO ##
## INFO ##

# Import python modules
from sys import argv

# Import kb modules
from kb.RPi2 import Context, Event

#------------------------------------------------------------------------------#
def scenario_1():
    """
    Declare events with the decorator based API
    """

    # Create containers
    context = Context()
    event   = Event(context)

    @event
    def on_start(context, event):
        print(context, '=>', event)
        print('STARTED')

    @event
    def on_cycle_begin(context, event):
        print('LOOP STARTED')

    @event
    def on_cycle_end(context, event):
        print('LOOP FINISHED')
        context.stop()

    @event
    def on_stop(context, event):
        print('FINISHED')
        context.exit()

    @event
    def on_exit(context, event):
        print('EXITING')

    # Make event active
    event.activate()
    # Start looping
    context.start()


#------------------------------------------------------------------------------#
def scenario_2():
    """
    Declare system with the inheritance based API
    """
    class MyEvent(Event):

        def on_start(self, context, event):
            print(context, '=>', event)
            print('STARTED')

        def on_cycle_begin(self, context, event):
            print('LOOP STARTED')

        def on_cycle_end(self, context, event):
            print('LOOP FINISHED')
            context.stop()

        def on_stop(self, context, event):
            print('FINISHED')
            context.exit()

        def on_exit(self, context, event):
            print('EXITING')


    context = Context()
    event   = MyEvent(context)

    # Make event active
    event.activate()
    # Start looping
    context.start()


#------------------------------------------------------------------------------#
# Run scenario
try:
    _, index = argv
except ValueError:
    index = 1
globals()['scenario_{}'.format(index)]()
