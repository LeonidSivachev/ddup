#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../parse.h"
#include "tests.h"

#define START_TEST(n)  printf("Starting test number %d!\n", n);
#define FINISH_TEST(n) printf("Test number %d succeeded!\n", n);

static bool check(config_t *config)
{
  bool ret = 1;

  ret = ret && (!strcmp(gconfig.loader_disk, config->loader_disk));
  ret = ret && (!strcmp(gconfig.loader_img, config->loader_img));
  ret = ret && (!strcmp(gconfig.system_disk, config->system_disk));
  ret = ret && (!strcmp(gconfig.system_img, config->system_img));
  ret = ret && (gconfig.verify == config->verify);
  ret = ret && (gconfig.bs == config->bs);
  ret = ret && (gconfig.compress == config->compress);

  return ret;
}

void test_parse()
{
  char *test_str[] = {"./ddup", "--loader-disk", "/dev/sda1", "--system-disk",
                      "/dev/sda2"};

  config_t config = {.loader_disk = "/dev/sda1",
                     .loader_img  = DEFAULT_LOADER_IMG,
                     .system_disk = "/dev/sda2",
                     .system_img  = DEFAULT_SYSTEM_IMG,
                     .verify      = DEFAULT_VERIFY,
                     .bs          = DEFAULT_BS,
                     .compress    = DEFAULT_COMPRESS};

  START_TEST(1);
  parse(5, test_str);
  assert(check(&config));
  FINISH_TEST(1);
}
