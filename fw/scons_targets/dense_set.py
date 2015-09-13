## INFO ##
## INFO ##

# Import python modules
from os.path import join

target = join('tests', 'bins', 'dense_set')
source = join('tests', 'dense_set.c'), join('kb', 'utils', 'dense_set.c')

def build(environment,
          path_prefixer):
    environment.Program(target = target,
                        source = [source[0]] + path_prefixer(source[1:]))
