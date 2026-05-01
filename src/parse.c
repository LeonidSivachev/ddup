#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"

config_t gconfig;

#ifdef DEBUG
static void print_config()
{
  printf("=== CURRENT CONFIGURATION ===\n");
  printf("Loader disk       : %s\n", gconfig.loader_disk);
  printf("Loader disk image : %s\n", gconfig.loader_img);
  printf("System disk       : %s\n", gconfig.system_disk);
  printf("System disk image : %s\n", gconfig.system_img);
  printf("Will verify       : %s\n", gconfig.verify ? "true" : "false");
  printf("Will compress     : %s\n", gconfig.compress ? "true" : "false");
  printf("Size of chunk     : %zu\n", gconfig.bs);
  printf("=============================\n");
}
#endif

static int parse_size(const char *str, size_t *byte_size)
{
  char *end;
  *byte_size = strtoul(str, &end, 10);

  if (end == str)
    return -1;

  switch (*end)
  {
  case 'K':
  case 'k':
    *byte_size <<= 10;
    return 0;
  case 'M':
  case 'm':
    *byte_size <<= 20;
    return 0;
  case 'G':
  case 'g':
    *byte_size <<= 30;
    return 0;
  case '\0':
    return 0;
  }
  return -1;
}

int parse(int argc, char *argv[])
{
  gconfig.loader_disk = INCORRECT_LOADER_DISK;
  gconfig.loader_img  = DEFAULT_LOADER_IMG;
  gconfig.system_disk = INCORRECT_SYSTEM_DISK;
  gconfig.system_img  = DEFAULT_SYSTEM_IMG;
  gconfig.verify      = DEFAULT_VERIFY;
  gconfig.bs          = DEFAULT_BS;
  gconfig.compress    = DEFAULT_COMPRESS;

  // clang-format off
  struct option long_options[] = {
    {"loader-disk", required_argument, 0, 'l'},
    {"loader-img" , required_argument, 0, 'L'},
    {"system-disk", required_argument, 0, 's'},
    {"system-img" , required_argument, 0, 'S'},
    {"verify"     , no_argument      , 0, 'v'},
    {"no-verify"  , no_argument      , 0, 'V'},
    {"compress"   , no_argument      , 0, 'c'},
    {"no-compress", no_argument      , 0, 'C'},
    {"bs"         , required_argument, 0, 'b'},
    {"help"       , no_argument      , 0, 'h'},
    {0            , 0                , 0,  0 }
  };
  // clang-format on

  int opt;
  int option_index;
  while (1)
  {
    opt =
        getopt_long(argc, argv, "l:L:s:S:b:vVcCh", long_options, &option_index);

    if (opt == -1)
      break;

    switch (opt)
    {
    case 'l':
      gconfig.loader_disk = optarg;
      break;
    case 'L':
      gconfig.loader_img = optarg;
      break;
    case 's':
      gconfig.system_disk = optarg;
      break;
    case 'S':
      gconfig.system_img = optarg;
      break;
    case 'v':
      gconfig.verify = true;
      break;
    case 'V':
      gconfig.verify = false;
      break;
    case 'c':
      gconfig.compress = true;
      break;
    case 'C':
      gconfig.compress = false;
      break;
    case 'h':
      printf(HELP_INFORMATION);
      return HELP_EXIT;
    case 'b':
      if (parse_size(optarg, &gconfig.bs))
      {
        fprintf(stderr, "Error: invalid block size '%s'\n", optarg);
        return -1;
      }
      break;
    case '?':
      fprintf(
          stderr,
          "Usage: ddup --loader-disk <dev> --system-disk <dev> [options]\n");
      return -1;
    }
  }

#ifdef DEBUG
  print_config();
#endif

  if (optind < argc)
  {
    fprintf(stderr, "Error: unexpected argument '%s'\n", argv[optind]);
    return -1;
  }

  if (gconfig.loader_disk == INCORRECT_LOADER_DISK)
  {
    fprintf(stderr, "Error: please specify a disk with loader!\n");
    fprintf(stderr, "Example: ddup --loader-disk /dev/sda1.\n");
    return -1;
  }

  if (gconfig.system_disk == INCORRECT_SYSTEM_DISK)
  {
    fprintf(stderr, "Error: please specify a disk with system!\n");
    fprintf(stderr, "Example: ddup --system-disk /dev/sda2.\n");
    return -1;
  }

  return 0;
}
