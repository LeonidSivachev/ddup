#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_LOADER_IMG "loader.img.backup"
#define DEFAULT_SYSTEM_IMG "system.img.backup"
#define DEFAULT_VERIFY     true
#define DEFAULT_BS         4 << 20 /* 4 Mega Bytes. */
#define DEFAULT_BS_STR     "4M"
#define DEFAULT_COMPRESS   true

#define INCORRECT_LOADER_DISK NULL
#define INCORRECT_SYSTEM_DISK NULL

#define HELP_EXIT 1
#define HELP_INFORMATION                                                       \
  "Usage: ddup [OPTIONS]\n"                                                    \
  "\n"                                                                         \
  "Options:\n"                                                                 \
  "  --loader-disk <dev>   source device for bootloader\n"                     \
  "  --system-disk <dev>   source device for system\n"                         \
  "  --loader-img  <file>  output image for bootloader "                       \
  "(default: " DEFAULT_LOADER_IMG ")\n"                                        \
  "  --system-img  <file>  output image for system     "                       \
  "(default: " DEFAULT_SYSTEM_IMG ")\n"                                        \
  "  --bs          <size>  block size, e.g. 4M         "                       \
  "(default: " DEFAULT_BS_STR ")\n"                                            \
  "  --verify              verify after backup\n"                              \
  "  --no-verify           skip verification\n"                                \
  "  --compress            compress output\n"                                  \
  "  --no-compress         skip compression\n"                                 \
  "  --help                show this help\n"

typedef struct
{
  char *loader_disk;
  char *loader_img;
  char *system_disk;
  char *system_img;
  bool verify;
  size_t bs;
  bool compress;
} config_t;

extern config_t gconfig;

int parse(int argc, char *argv[]);
#endif /* PARSE_H */
