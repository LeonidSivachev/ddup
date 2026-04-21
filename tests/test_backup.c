#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../backup.h"
#include "tests.h"

/*
 * Now it's wrong, Claud write something
 * about 'loop device'.
 * TODO: fix it.
 */
static int create_test_disk(char *path, size_t size, int *fdes)
{
  /* TODO: think about parameters for open(). */
  int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR);
  if (fd == -1)
  {
    /* TODO: add output with errno interpretaion. */
    fprintf(stderr, "Error, fail attempt to create disk!\n");
    return -1;
  }

  if (ftruncate(fd, size) == -1)
  {
    /*
     * TODO: add output with errno interpretation.
     * Maybe we should add close error handling
     * here and further.
     */
    fprintf(stderr, "Error, fail to icrease file size!\n");
    close(fd);
    return -1;
  }

  *fdes = fd;
  return 0;
}

int test_get_size()
{
  int fd;
  /* TODO: move constants to define. */
  create_test_disk("test.img", 4 << 10, &fd);

  size_t size;
  if (get_disk_size(fd, &size) != 0)
  {
    close(fd);
    fprintf(stderr, "get_disk_size returned error!\n");
    return -1;
  }

  if (size != (4 << 10))
  {
    close(fd);
    fprintf(stderr, "Wrong size from get_disk_size!\n");
    return -1;
  }

  printf("Everything is fine! test_get_size work correctly!\n");
  close(fd);

  return 0;
}
