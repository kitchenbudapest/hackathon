## INFO ##
## INFO ##

# Import python modules
from sys import exit

# Import kb modules
from kb.RPi2.pin import Pin, PinIsNotGPIO
from kb.RPi2     import ignorable_callback


#------------------------------------------------------------------------------#
class Context:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self):
        self._events   = set()
        self._activate = None
        self._looping  = False
        self._exit     = False

        # Callback containers
        self._on_start_callbacks        = set()
        self._on_cycle_begin_callbacks  = set()
        self._on_cycle_end_callbacks    = set()
        self._on_stop_callbacks         = set()
        self._on_event_switch_callbacks = set()
        self._on_exit_callbacks         = set()


    # Storage management
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def bind_events(self, *events):
        """Add events to context"""
        self._events.update(events)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def unbind_events(self, *events):
        """Remove events from context if they are present"""
        all_events = self._events
        for event in events:
            try:
                all_events.remove(event)
            except KeyError:
                pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def activate_event(self, event):
        """Active already bound event in context"""
        # If event not bound to context
        if event not in self._events:
            raise ValueError('Event is not in Context: {!r}'.format(event))
        # If there is an active event and context is in a loop
        elif (self._active is not None and
              self._looping):
                self._activate = event
        # If this is the first time an event is
        # activated or context is not looping
        else:
            self._active = event


    # Loop control
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def start(self):
        # Check if there is an active event set
        try:
            active = self._active
        except AttributeError:
            raise AttributeError('Context object has no '
                                 'active event set') from None

        # Get local references
        on_cycle_begin = self.on_cycle_begin
        on_cycle_end   = self.on_cycle_end

        # Set values
        self._looping  = True

        # Invoke callbacks
        active.on_start()

        # Enter event-loop
        while self._looping:
            # Get local reference
            active = self._active

            # Invoke callbacks
            active.on_cycle_begin()

            # Go through all pins
            for pin in active.pins():
                if pin.signaled:
                    pin.on_signal()

            # Invoke callbacks
            active.on_cycle_end(self)

            # If event-switching has been scheduled
            if (self._switch is not None):
                    self.on_event_switch(self, active, self._switch)
                    active.reset_pins()
                    self._active = self._switch
                    self._switch = None

        # Invoke callbacks
        self._active.on_stop(self)

        # If program wants to exit
        if self._exit:
            # Invoke callbacks
            self.on_exit(self._active)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def stop(self):
        self._looping = False


    # Program control
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def exit(self):
        self._exit = True


    # Hardware controls
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @_Context_event_callback
    def reset_pins(self):
        try:
            active = self._active
        except AttributeError:
            raise AttributeError('Context object has no active Event set') from None
        active.reset_pins()


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def pin(self, pin_id):
        try:
            pin = Pin(pin_id)
            self._active.pins.append(pin)
            return pin
        except PinIsNotGPIO:
            raise ValueError('Pin #{} is not a data pin'.format(pin_id)) from None


    # Events
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def _get_callbacks(self, callback):
        try:
            return getattr(self, '_' + callback.__name__ + '_callbacks')
        except AttributeError:
            raise ValueError('Context object has no callback: '
                             '{!r}'.format(callback.__name__)) from None


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        self.bind_callbacks(callback)
        return callback


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def bind_callbacks(self, **callbacks):
        for name, function in callbacks.items()
            try:



    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def unbind_callbacks(self, **callbacks):
        """Remove callbacks if they are present"""
        try:
            callbacks = self._get_callbacks(callback)
        except ValueError:
            raise ValueError('Context object has no stored '
                             'callback: {!r}'.format(callback)) from None
        for
            .remove(callback)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_start(self, event):
        """Called only once per loop, when starting the loop"""
        for callback in self._on_start_callbacks:
            callback(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_cycle_begin(self, event):
        """Called at the beginning of every cycle"""
        for callback in self._on_cycle_begin_callbacks:
            callback(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_cycle_end(self, event):
        """Called at the end of every cycle"""
        for callback in self._on_cycle_end_callbacks:
            callback(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_event_switch(self, prev_event,
                              next_event):
        """Called after Contextis switching Event"""
        for callback in self._on_event_switch_callbacks:
            callback(self, prev_event, next_event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_stop(self, event):
        """Called only once per loop, when stopping loop"""
        for callback in self._on_stop_callbacks:
            callback(self, event)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_exit(self, event):
        """Called at the end of the program"""
        for callback in self._on_exit_callbacks:
            callback(self, event)
        self.reset_pins()
        exit()
