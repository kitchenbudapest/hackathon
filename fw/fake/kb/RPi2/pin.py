## INFO ##
## INFO ##

#------------------------------------------------------------------------------#
class PinIsNotGPIO(Exception): pass


#------------------------------------------------------------------------------#
class Pin:

    GPIO = {'1',
            '2',
            '3'}

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, pin_id, sensor):
        if pin_id not in GPIO:
            raise PinIsNotGPIO(pin_id)
        self._id    = pin_id
        self._state = False


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __call__(self, callback):
        """Set callback"""
        setattr(self, callback.__name__, callback)
        return callback


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_high(self, sensor, event, context):
        print('Pin #{}: received a HIGH signal'.format(self._id))


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def on_low(self, sensor, event, context):
        print('Pin #{}: received a LOW signal'.format(self._id))


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def reset(self):
        pass


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def set_high(self):
        self.on_high(**self.sensor.callback_args)
        self._state = True


    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def set_low(self):
        self.on_low(**self.sensor.callback_args)
        self._state = False
