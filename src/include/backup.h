#ifndef BACKUP_H
#define BACKUP_H

void backup_disk(const char *src, const char *dst);

#ifdef TESTING
int get_disk_size(int, size_t *);
#endif

#endif
