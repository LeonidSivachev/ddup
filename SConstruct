SetOption('no_progress', 1)

mode = ARGUMENTS.get('mode', 'debug')
cc = ARGUMENTS.get('cc', 'clang')

available_modes = Split('release debug')
available_compilers = Split('gcc clang')

if mode not in available_modes:
    print(f'ERROR: UNAVAILABLE MODE = {mode}!')
    Exit(1)

if cc not in available_compilers:
    print(f'ERROR: UNAVAILABLE COMPILER = {cc}!')
    Exit(1)

# Will be, when minimal prototype will be finished.
# cflags = Split('-Wall -Wextra -Werror')
cflags = []
cppdefines = []
src = Split('main.c parse.c')
target = 'ddup'

if mode == 'debug':
    print(f'Build in debug mode via {cc}!')
    cflags += Split('-O0 -g')
    cppdefines += ['DEBUG']

if mode == 'release':
    print(f'Build in release mode via {cc}!')
    cflags += Split('-O2')

env = Environment(
        CPPDEFINES=cppdefines,
        CC=cc,
        CFLAGS=cflags)

env.Program(target, src)
