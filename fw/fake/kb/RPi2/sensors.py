## INFO ##
## INFO ##


#------------------------------------------------------------------------------#
class Sensor:
    """
    Base class of all sensors

    Available public methods:
        enable
        disable

    Available callbacks:
        on_enable
        on_disable
    """

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, event):
        # Create connection
        event.bind_sensor(self)
        self._event   = event
        self._context = event.context
        self._enabled = True


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        """Set callback"""
        setattr(self, callback.__name__, callback)
        return callback


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_enable(self, *args, **kwargs):
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_disable(self, *args, **kwargs):
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def enable(self):
        self.on_enable(self._event, self._context)
        self._enabled = True


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def disable(self):
        self.on_disable(self._event, self._context)
        self._enabled = False



#------------------------------------------------------------------------------#
class LED(Sensor):

    """
    Available inherited public methods:
        enable
        disable

    Available public methods:
        on
        off

    Available inherited callbacks:
        on_enable
        on_disable

    Available callbacks:
        on_on
        on_off
    """

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, event,
                       pin):
        # Initialize Sensor
        super().__init__(event)
        self._pin = pin


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on(self):
        """Turn LED ON"""
        self.on_on(self._event, self._context)
        self._pin.set_high()


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def off(self):
        """Turn LED OFF"""
        self.on_off(self._event, self._context)
        self._pin.set_low()



#------------------------------------------------------------------------------#
class FourKeys(Sensor):

    """
    Available inherited public methods:
        enable
        disable

    Available inherited callbacks:
        on_enable
        on_disable

    Available callback methods:
        FourKeys.on_key_pressed_1
        FourKeys.on_key_pressed_2
        FourKeys.on_key_pressed_3
        FourKeys.on_key_pressed_4
    """

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, event,
                       pin_row,
                       pin_col1,
                       pin_col2,
                       pin_col3,
                       pin_col4):
        # Initialize Sensor
        super().__init__(event)

        # Setup callbacks
        @event.pin(pin_col1)
        def on_signal_high(context, event, sensor):
            self.on_key_pressed_1(context, event, sensor)

        @event.pin(pin_col2)
        def on_signal_high(*args, **kwargs):
            self.on_key_pressed_2(*args, **kwargs)

        @event.pin(pin_col3)
        def on_signal_high(*args, **kwargs):
            self.on_key_pressed_2(*args, **kwargs)

        @event.pin(pin_col4)
        def on_signal_high(*args, **kwargs):
            self.on_key_pressed_2(*args, **kwargs)


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_key_pressed_1(self):
        """Invoked when key #1 pressed on the matrix keyboard"""
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_key_pressed_2(self):
        """Invoked when key #2 pressed on the matrix keyboard"""
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_key_pressed_3(self):
        """Invoked when key #3 pressed on the matrix keyboard"""
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_key_pressed_4(self):
        """Invoked when key #4 pressed on the matrix keyboard"""
        pass
