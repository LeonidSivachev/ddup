#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_LOADER_IMG "loader.img.backup"
#define DEFAULT_SYSTEM_IMG "system.img.backup"
#define DEFAULT_VERIFY     true
#define DEFAULT_BS         4 << 20 /* 4 Mega Bytes. */
#define DEFAULT_COMPRESS   true

#define INCORRECT_LOADER_DISK NULL
#define INCORRECT_SYSTEM_DISK NULL

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
