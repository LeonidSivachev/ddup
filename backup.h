#ifndef BACKUP_H
#define BACKUP_H

#include <stdlib.h>

#ifdef DEBUG
int get_disk_size(int, size_t *);
#else
static get_disk_size(int, size_t *);
#endif

#endif
