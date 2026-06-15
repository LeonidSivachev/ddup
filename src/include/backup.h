#ifndef BACKUP_H
#define BACKUP_H
#include <stddef.h>

int backup_disk(const char *src, const char *dst);
void backup_disk_verified(const char *src, const char *dst, char *digestname,
                          unsigned char *md_value, unsigned int *md_len);

#ifdef TESTING
int get_disk_size(int, size_t *);
int print_progress(size_t, size_t);
void sigwinch_handler(int);
#endif

#endif
