#include <linux/fs.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "backup.h"

#ifdef TESTING
int get_disk_size(int fd, size_t *size)
#else
static int get_disk_size(int fd, size_t *size)
#endif
{
  if (ioctl(fd, BLKGETSIZE64, size))
  {
    fprintf(stderr, "Error!\n");
    return -1;
  }

  return 0;
}
