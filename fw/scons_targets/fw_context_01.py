## INFO ##
## INFO ##

# Import python modules
from os.path import join

target = join('tests', 'bins', 'fw_context_01')
source = (join('tests', 'fw_context_01.c'),
          join('kb', 'utils', 'dense_set.c'),
          join('kb', 'rpi2', 'contexts.c'),
          join('kb', 'rpi2', 'events.c'),
          join('kb', 'rpi2', 'sensors.c'),
          join('kb', 'rpi2', 'pins.c'))

def build(environment,
          path_prefixer):
    environment.Program(target = target,
                        source = [source[0]] + path_prefixer(source[1:]))
