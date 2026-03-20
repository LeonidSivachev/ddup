#ifndef PARSE_H
#define PARSE_H

#include <stddef.h>
#include <stdbool.h>

#define DEFAULT_LOADER_IMG "loader.img.backup"
#define DEFAULT_SYSTEM_IMG "system.img.backup"
#define DEFAULT_VERIFY     true
#define DEFAULT_BS    	   "4M"
#define DEFAULT_COMPRESS   true

typedef struct
{
	char *loader_disk;
	char *loader_img;
	char *system_disk;
	char *system_img;
	bool verify;
	size_t bs;
	bool compress;
} config_t;

extern config_t gconfig;

int parse(int argc, char *argv[]);
#endif /* PARSE_H */
