## INFO ##
## INFO ##

#------------------------------------------------------------------------------#
class Sensor:
    """
    Base class of all sensors
    """

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        setattr(self, callback.__name__, callback)



#------------------------------------------------------------------------------#
class LED(Sensor):
    pass



#------------------------------------------------------------------------------#
class FourKeys(Sensor):

    def __init__(self, event,
                       pin_row,
                       pin_col1,
                       pin_col2,
                       pin_col3,
                       pin_col4):
        self._event = event
        event.bind_sensor(self)

        @event.pin(pin_col1)
        def on_signal(context, event, sensor):
            self.on_key_pressed_1(context, event, sensor)

        @event.pin(pin_col2)
        def on_signal(*args, **kwargs):
            self.on_key_pressed_2(*args, **kwargs)
