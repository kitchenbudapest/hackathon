## INFO ##
## INFO ##

# Import kb modules
from kb.utils import binder_interface

#------------------------------------------------------------------------------#
@binder_interface('on_start', 'on_stop')
class Event:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, context):
        # Create relations
        self._context = context
        context.bind_events(self)

        # Create containers
        self._pins = []


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def activate(self):
        self._context.activate_event(self)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def reset_pins(self):
        for pin in self._pins:
            pin.reset()


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def pins(self):
        yield from self._pins


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        """Set callback"""
        setattr(self, callback.__name__, callback)
        return callback
