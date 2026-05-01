SetOption('no_progress', 1)

mode = ARGUMENTS.get('mode', 'debug')
cc = ARGUMENTS.get('cc', 'clang')
available_modes = Split('release debug testing')
available_compilers = Split('gcc clang')
# TEMPORARY!
cflags = Split('-Wall -Wextra')
# cflags = Split('-Wall -Wextra -Werror')
cppdefines = []
src = Glob('src/*.c')
headers = Glob('src/*.h')
testing_src = Glob('tests/*.c')
testing_headers = Glob('tests/*.h')
target = 'ddup'
debug_flags = Split('-O0 -g')
release_flags = Split('-O2')

if mode not in available_modes:
    print(f'ERROR: UNAVAILABLE MODE = {mode}!')
    Exit(1)

if cc not in available_compilers:
    print(f'ERROR: UNAVAILABLE COMPILER = {cc}!')
    Exit(1)

if cc == 'clang':
    cflags.append('-fcolor-diagnostics')
if cc == 'gcc':
    cflags.append('-fdiagnostics-color=always')

print(f'Build in {mode} mode via {cc}!')

if mode == 'debug':
    cflags += debug_flags
    cppdefines += ['DEBUG']

if mode == 'release':
    cflags += release_flags

if mode == 'testing':
    cflags += debug_flags
    cppdefines += ['TESTING']
    src = [f for f in Glob('src/*.c') if f.name != 'main.c']
    src += testing_src
    headers += testing_headers

env = Environment(
        CPPDEFINES=cppdefines,
        CPPPATH=['src/include/', 'tests/include/'],
        CC=cc,
        CFLAGS=cflags,
        OBJPREFIX='build/')

objects = []
for f in src:
    obj = env.Object(f'{f.name[:-2]}.o', f)
    objects.append(obj)

env.Program(target, objects)
