#include <errno.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "backup.h"
#include "parse.h"

#ifdef TESTING
int get_disk_size(int fd, size_t *size)
#else
static int get_disk_size(int fd, size_t *size)
#endif
{
  if (ioctl(fd, BLKGETSIZE64, size))
    return -1;

  return 0;
}

void backup_disk(const char *src, const char *dst)
{
  int src_fd      = -1;
  int dst_fd      = -1;
  uint8_t *buf    = NULL;
  size_t src_size = 0;
  size_t written  = 0;

  src_fd = open(src, O_RDONLY);
  if (src_fd == -1)
  {
    fprintf(stderr, "Error: failed to open source '%s': %s\n", src,
            strerror(errno));
    goto cleanup;
  }

  /* TODO: think about mode(0644) */
  dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (src_fd == -1)
  {
    fprintf(stderr, "Error: failed to open destination '%s': %s\n", dst,
            strerror(errno));
    goto cleanup;
  }

  if (get_disk_size(src_fd, &src_size) == -1)
  {
    fprintf(stderr, "Error: failed to determine disk size '%s'\n", src);
    goto cleanup;
  }

#ifdef DEBUG
  printf("Disk size is %zu!\n", src_size);
#endif

  buf = malloc(gconfig.bs);
  if (buf == NULL)
  {
    fprintf(stderr, "Error: failed to allocate buffer\n");
    goto cleanup;
  }

  while (written < src_size)
  {
    size_t to_read    = gconfig.bs;
    ssize_t read_res  = 0;
    ssize_t write_res = 0;

    if (written + to_read > src_size)
      to_read = src_size - written;

    read_res = read(src_fd, buf, to_read);

    if (read_res == -1)
    {
      fprintf(stderr, "Error: read failed from '%s': %s\n", src,
              strerror(errno));
      goto cleanup;
    }

    if (read_res == 0)
      break;

    write_res = write(dst_fd, buf, to_read);

    if (write_res != read_res)
    {
      fprintf(stderr, "Error: failed write to '%s': %s\n", dst,
              strerror(errno));
      goto cleanup;
    }

    written += read_res;
#ifdef DEBUG
    /*
     * TODO: implement function for comfortable recognition
     * count copied bytes (e.g. MB or KB)
     * Maybe we should add something like progress bar.
     */
    printf("Copied %zd byte!\n", read_res);
#endif
  }
#ifdef DEBUG
  printf("Successcully created disk image!\n");
#endif

cleanup:
  if (src_fd != -1)
    close(src_fd);
  if (dst_fd != -1)
    close(dst_fd);
  /* How I remember free(NULL) is valid operation,
   * but it should be checked. */
  free(buf);
}
