#include <openssl/evp.h>

#include "backup.h"
#include "parse.h"

#define AUTHOR "Leonid Sivachev"

int main(int argc, char *argv[])
{
  parse(argc, argv);

  if (gconfig.verify)
  {
    backup_disk_verified(gconfig.loader_disk, gconfig.loader_img);
    backup_disk_verified(gconfig.system_disk, gconfig.system_img);
  }
  else
  {
    backup_disk(gconfig.loader_disk, gconfig.loader_img);
    backup_disk(gconfig.system_disk, gconfig.system_img);
  }

  return 0;
}
