## INFO ##
## INFO ##

# Import python modules
from sys import exit

#------------------------------------------------------------------------------#
def _Context_event_callback(method):
    def bypassable(*args, **kwargs):
        try:
            method(*args, **kwargs)
        except AttributeError:
            raise AttributeError('Context object has '
                                 'no active event') from None
    return bypassable



#------------------------------------------------------------------------------#
class Context:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self):
        self._pins    = []
        self._events  = []
        self._active  = None
        self._switch  = None
        self._looping = False
        self._exit    = False


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # Storage management
    def bind_events(self, *events):
        self._events.extend(events)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def switch_event(self, event):
        # If event nout bound to context
        if event not in self._events:
            raise ValueError('Event is not in Context')
        # If there is an active event and context is in a loop
        elif (self._active is not None and
              self._looping):
                self._switch = event
        # If this is the first time an event is
        # activated or context is not looping
        else:
            self._active = event


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # Loop control
    def start(self):
        self._looping  = True
        on_cycle_begin = self.on_cycle_begin
        on_cycle_end   = self.on_cycle_end

        self.on_start(self._active)
        while self._looping:
            active = self._active
            on_cycle_begin(active)

            # for pin in pins => if signal => on_signal(pin)

            on_cycle_end(active)

            # If event-switching has been scheduled
            if (self._switch is not None):
                    self.on_event_switch(self, active, self._switch)
                    self._active = self._switch
                    self._switch = None

        self.on_stop(self._active)
        if self._exit:
            self.on_exit(self._active)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def stop(self):
        self._looping = False


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # Program control
    def exit(self):
        self._exit = True


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # Hardware controls
    def reset_pins(self):
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # Events
    @_Context_event_callback
    def on_start(self, event):
        """Called only once per loop, when start looping"""
        self._active.on_start(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_cycle_begin(self, event):
        """Called at the beginning of every cycle"""
        self._active.on_cycle_begin(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_cycle_end(self, event):
        """Called at the end of every cycle"""
        self._active.on_cycle_end(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_signal(self, event, pin):
        self._active.on_signal(self, event, pin)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_event_switch(self, prev_event,
                              next_event):
        """Called after Context.switch_event() called"""
        self._active.on_event_switch(self, prev_event, next_event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_stop(self, event):
        """Called only once per loop, when stop looping"""
        self._active.on_stop(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def on_exit(self, event):
        """Called at the end of the program"""
        self._active.on_exit(self, event)
        self.reset_pins()
        exit()



#------------------------------------------------------------------------------#
class Event:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, context):
        self._context = context
        context.bind_events(self)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def activate(self):
        self._context.switch_event(self)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        """Set callback"""
        setattr(self, callback.__name__, callback)
