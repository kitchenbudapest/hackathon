## INFO ##
## INFO ##

# Import python modules
from os.path import join

target = join('tests', 'bins', 'fw_context_02')
source = (join('tests', 'fw_context_02.c'),
          join('kb', 'errors.c'),
          join('kb', 'utils', 'dense_set.c'),
          join('kb', 'rpi2', 'contexts.c'),
          join('kb', 'rpi2', 'events.c'),
          join('kb', 'rpi2', 'sensors.c'),
          join('kb', 'rpi2', 'sensors', 'leds.c'),
          join('kb', 'rpi2', 'sensors', 'four_keys.c'),
          join('kb', 'rpi2', 'pins.c'))

def build(environment,
          path_prefixer):
    environment.Program(target = target,
                        source = [source[0]] + path_prefixer(source[1:]))
