## ddup - disk dump

Simple utility for creating disk backups. Written in C, built via SCons.
Can be built only on Linux-based operating systems.

### Idea
The intended workflow is to boot from a Live CD, create backups of the bootloader
and system partitions to an external drive. In case of system failure or disk
replacement, the backups can be used to quickly restore the system to its
previous state.

### Build modes
- **debug** — no optimizations, debug info, extra logs.
- **testing** — no optimizations, debug info, tests for main functions.
- **release** — O2 optimization, no debug info, warnings treated as errors.

### Supported compilers
- **clang**
- **gcc**

### Build
From the root directory:
```bash
scons mode=<mode> cc=<compiler>
```
Example:
```bash
scons mode=release cc=clang
```
Default (just `scons`) builds with clang in debug mode.

### Usage
To get information about interface use:
```bash
./ddup --help
```
### Status
Project is currently under development. Not all features listed in `--help` are implemented yet.
