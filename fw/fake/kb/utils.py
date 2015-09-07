## INFO ##
## INFO ##

#------------------------------------------------------------------------------#
def ignorable_callback(method):
    """
    Wrapper to ignore callback if it is not present, but also 'saves' the
    AttributeError for other errors raised during the method call.
    """
    def callback(self, *args, **kwargs):
        # If method is defined for instance
        try:
            method = getattr(self, method.__name__)
        # If method cannot be found
        except AttributeError:
            return
        # Invoke method
        return method(self, *args, **kwargs)
    # Return wrapped method
    return callback



#------------------------------------------------------------------------------#
def binder_interface(cls, *bindables):
    xxx = {}
    for bindable in bindables:
        container

    bindables = {b: {'container': '_' + b + '_callbacks',
                      for
    }

    # Wrap initializer
    original_init = cls.__init__
    def modified_init(self, *args, **kwargs):
        instance = original_init(self, *args, **kwargs)
        for bindable in bindables:
            setattr(instance,
        return instance

    cls.__init__ = modified_init
