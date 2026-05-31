#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "backup.h"
#include "parse.h"

#define CURSOR_UP   "\033[1A"
#define CURSOR_DOWN "\033[1B"
#define CLEAR_LINE  "\033[2K"

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

static volatile sig_atomic_t terminal_resized = 0;

#ifdef TESTING
void sigwinch_handler(int sig)
#else
static void sigwinch_handler(int sig)
#endif
{
  (void)sig;
  terminal_resized = 1;
}

#ifdef TESTING
int print_progress(size_t written, size_t size)
#else
static int print_progress(size_t written, size_t size)
#endif
{
#ifdef DEBUG
  assert(written <= size);
#endif

  static unsigned short bar_len;

  if (terminal_resized || !written)
  {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
      return -1;

    unsigned short new_bar_len = w.ws_col - 2;

    if (bar_len != 0)
    {
      unsigned short lines_to_clear = (bar_len + 2) / (new_bar_len + 2);
      if (bar_len % new_bar_len != 0)
        ++lines_to_clear;

      for (int i = 0; i < lines_to_clear; ++i)
        printf(CLEAR_LINE CURSOR_UP);
      printf(CURSOR_DOWN);
    }

    bar_len          = new_bar_len;
    terminal_resized = 0;
  }

  unsigned short progres = (unsigned short)((double)written / size * bar_len);

  if (written != 0)
  {
    printf("\r");
  }

  char ch;
  printf("[");
  for (unsigned short i = 0; i < bar_len; ++i)
  {
    ch = (i < progres) ? '#' : '.';
    printf("%c", ch);
  }
  printf("]");

  fflush(stdout);

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

  signal(SIGWINCH, sigwinch_handler);
  print_progress(0, src_size);
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
    print_progress(written, src_size);
#ifdef DEBUG
    /*
     * TODO: implement function for comfortable recognition
     * count copied bytes (e.g. MB or KB)
     * Maybe we should add something like progress bar.
     */
    // printf("Copied %zd byte!\n", read_res);
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
