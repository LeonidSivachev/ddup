#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "../parse.h"
#include "tests.h"

#define START_TEST(n)                                                          \
  printf("Starting test number %d...\n", n);                                   \
  optind = 1;
#define FINISH_TEST(n) printf("Test number %d succeeded!\n\n", n);

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

static int argv_len(char *argv[])
{
  int len = 0;
  while (argv[len] != NULL)
    len++;
  return len;
}

void test_parse()
{
  // Test 1: minimal required args
  {
    START_TEST(1);
    char *argv[]    = {"./ddup",        "--loader-disk", "/dev/sda1",
                       "--system-disk", "/dev/sda2",     NULL};
    config_t config = {.loader_disk = "/dev/sda1",
                       .loader_img  = DEFAULT_LOADER_IMG,
                       .system_disk = "/dev/sda2",
                       .system_img  = DEFAULT_SYSTEM_IMG,
                       .verify      = DEFAULT_VERIFY,
                       .bs          = DEFAULT_BS,
                       .compress    = DEFAULT_COMPRESS};
    parse(argv_len(argv), argv);
    assert(check(&config));
    FINISH_TEST(1);
  }

  // Test 2: custom images
  {
    START_TEST(2);
    char *argv[]      = {"./ddup",        "--loader-disk",
                         "/dev/sda1",     "--system-disk",
                         "/dev/sda2",     "--loader-img",
                         "my_loader.img", "--system-img",
                         "my_system.img", NULL};
    config_t expected = {.loader_disk = "/dev/sda1",
                         .loader_img  = "my_loader.img",
                         .system_disk = "/dev/sda2",
                         .system_img  = "my_system.img",
                         .verify      = DEFAULT_VERIFY,
                         .bs          = DEFAULT_BS,
                         .compress    = DEFAULT_COMPRESS};
    parse(argv_len(argv), argv);
    assert(check(&expected));
    FINISH_TEST(2);
  }

  // Test 3: custom block size
  {
    START_TEST(3);
    char *argv[] = {"./ddup",    "--loader-disk", "/dev/sda1", "--system-disk",
                    "/dev/sda2", "--bs",          "1M",        NULL};
    config_t expected = {.loader_disk = "/dev/sda1",
                         .loader_img  = DEFAULT_LOADER_IMG,
                         .system_disk = "/dev/sda2",
                         .system_img  = DEFAULT_SYSTEM_IMG,
                         .verify      = DEFAULT_VERIFY,
                         .bs          = 1 << 20,
                         .compress    = DEFAULT_COMPRESS};
    parse(argv_len(argv), argv);
    assert(check(&expected));
    FINISH_TEST(3);
  }

  // Test 4: --no-verify --no-compress
  {
    START_TEST(4);
    char *argv[] = {
        "./ddup",    "--loader-disk", "/dev/sda1",     "--system-disk",
        "/dev/sda2", "--no-verify",   "--no-compress", NULL};
    config_t expected = {.loader_disk = "/dev/sda1",
                         .loader_img  = DEFAULT_LOADER_IMG,
                         .system_disk = "/dev/sda2",
                         .system_img  = DEFAULT_SYSTEM_IMG,
                         .verify      = false,
                         .bs          = DEFAULT_BS,
                         .compress    = false};
    parse(argv_len(argv), argv);
    assert(check(&expected));
    FINISH_TEST(4);
  }

  // Test 5: --verify --compress
  {
    START_TEST(5);
    char *argv[] = {"./ddup",    "--loader-disk", "/dev/sda1",  "--system-disk",
                    "/dev/sda2", "--verify",      "--compress", NULL};
    config_t expected = {.loader_disk = "/dev/sda1",
                         .loader_img  = DEFAULT_LOADER_IMG,
                         .system_disk = "/dev/sda2",
                         .system_img  = DEFAULT_SYSTEM_IMG,
                         .verify      = true,
                         .bs          = DEFAULT_BS,
                         .compress    = true};
    parse(argv_len(argv), argv);
    assert(check(&expected));
    FINISH_TEST(5);
  }

  // Test 6: missing --loader-disk -> error
  {
    START_TEST(6);
    char *argv[] = {"./ddup", "--system-disk", "/dev/sda2", NULL};
    assert(parse(argv_len(argv), argv) == -1);
    FINISH_TEST(6);
  }

  // Test 7: missing --system-disk -> error
  {
    START_TEST(7);
    char *argv[] = {"./ddup", "--loader-disk", "/dev/sda1", NULL};
    assert(parse(argv_len(argv), argv) == -1);
    FINISH_TEST(7);
  }

  // Test 8: unknown argument -> error
  {
    START_TEST(8);
    char *argv[] = {"./ddup",    "--loader-disk", "/dev/sda1", "--system-disk",
                    "/dev/sda2", "--unknown",     NULL};
    assert(parse(argv_len(argv), argv) == -1);
    FINISH_TEST(8);
  }

  // Test 9: superfluous argument -> error
  {
    START_TEST(9);
    char *argv[] = {"./ddup",    "--loader-disk", "/dev/sda1", "--system-disk",
                    "/dev/sda2", "something",     NULL};
    assert(parse(argv_len(argv), argv) == -1);
    FINISH_TEST(9);
  }

  // Test 10: block size Kb
  {
    START_TEST(10);
    char *argv[] = {"./ddup",    "--loader-disk", "/dev/sda1", "--system-disk",
                    "/dev/sda2", "--bs",          "512K",      NULL};
    config_t expected = {.loader_disk = "/dev/sda1",
                         .loader_img  = DEFAULT_LOADER_IMG,
                         .system_disk = "/dev/sda2",
                         .system_img  = DEFAULT_SYSTEM_IMG,
                         .verify      = DEFAULT_VERIFY,
                         .bs          = 512 << 10,
                         .compress    = DEFAULT_COMPRESS};
    parse(argv_len(argv), argv);
    assert(check(&expected));
    FINISH_TEST(10);
  }
}
