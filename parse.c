#include <stdio.h>

#include "parse.h"

config_t gconfig;

static void print_config()
{
  printf("=== CURRENT_CONFIGURATION ===\n");
  printf("Loader disk       : %s\n", gconfig.loader_disk);
  printf("Loader disk image : %s\n", gconfig.loader_img);
  printf("System disk       : %s\n", gconfig.system_disk);
  printf("System disk image : %s\n", gconfig.system_img);
  printf("Will verify       : %s\n", gconfig.verify ? "true" : "false");
  printf("Will compress     : %s\n", gconfig.compress ? "true" : "false");
  printf("Size of chunk     : %zu\n", gconfig.bs);
  printf("=============================\n");
}

int parse(int argc, char *argv[])
{
	gconfig.loader_img = DEFAULT_LOADER_IMG;
	gconfig.system_img = DEFAULT_SYSTEM_IMG;
  gconfig.verify     = DEFAULT_VERIFY;
  gconfig.compress   = DEFAULT_COMPRESS;

  char bs_buf[8];

  print_config();

  return 0;
}

