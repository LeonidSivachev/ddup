#include "backup.h"
#include "parse.h"

#define AUTHOR "Leonid Sivachev"

int main(int argc, char *argv[])
{
  parse(argc, argv);

  /* Backup loader disk. */
  backup_disk(gconfig.loader_disk, gconfig.loader_img);

  /* Backup system disk. */
  backup_disk(gconfig.system_disk, gconfig.system_img);

  return 0;
}
