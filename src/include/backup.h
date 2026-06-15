#ifndef BACKUP_H
#define BACKUP_H
#include <stddef.h>

int backup_disk(const char *src, const char *dst);

#ifdef TESTING
int get_disk_size(int, size_t *);
int print_progress(size_t, size_t);
void sigwinch_handler(int);
#endif

#endif
