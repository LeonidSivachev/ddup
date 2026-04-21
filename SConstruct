SetOption('no_progress', 1)

mode = ARGUMENTS.get('mode', 'debug')
cc = ARGUMENTS.get('cc', 'clang')

available_modes = Split('release debug testing')
available_compilers = Split('gcc clang')
# TEMPORARY!
cflags = Split('-Wall -Wextra') 
# cflags = Split('-Wall -Wextra -Werror')
cppdefines = []
# TODO: these files should be founded automatically.
src = Split('main.c parse.c backup.c')
headers = Split('parse.h backup.h')
testing_src = Split('tests/run_tests.c tests/test_backup.c tests/test_parse.c')
testing_headers = Split('tests/tests.h')
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

# TODO: Maybe we should use separate variable
# 'TESTING' instead of 'DEBUG'.
if mode == 'testing':
    cflags += debug_flags
    cppdefines += ['DEBUG']
    src.remove('main.c')
    src += testing_src
    headers += testing_headers

env = Environment(
        CPPDEFINES=cppdefines,
        CC=cc,
        CFLAGS=cflags)

env.Program(target, src)

# TODO: create separate executable file for formatting.
# env.Alias('format', env.Command('format', src + headers,
#    'clang-format -i ' + ' '.join(src + headers)))
