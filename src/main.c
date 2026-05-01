#include "backup.h"
#include "parse.h"

#define AUTHOR "Leonid Sivachev"

int main(int argc, char *argv[])
{
  parse(argc, argv);

  /* Backup loader disk. */
  backup_disk(gconfig.loader_disk, gconfig.loader_img);

  return 0;
}
