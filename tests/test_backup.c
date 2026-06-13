#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "backup.h"
#include "parse.h"
#include "tests.h"

#define DISK_NAME_SIZE   32
#define BACKUP_FILE_NAME "backup.img"

void test_backup()
{
  if (geteuid() != 0)
  {
    printf("Running this test requires \'sudo\'!\n");
    return;
  }

  printf("Enter the disk for testing: ");
  printf(
      "(example: /dev/sdb, the best option is using external flash device)\n");
  printf("> ");

  char disk_name[DISK_NAME_SIZE];
  fgets(disk_name, DISK_NAME_SIZE, stdin);
  disk_name[strcspn(disk_name, "\n")] = '\0';
  /*
   * NOTE: I don't like it, seems like creating global config is bad idea.
   * Maybe in I should fix it.
   */
  gconfig.bs = DEFAULT_BS;

  printf("Backing up %s ...\n", disk_name);
  backup_disk(disk_name, BACKUP_FILE_NAME);
  printf("Backup of %s completed successfully.\n", disk_name);

  /* TODO: Implement verification of image. */
}
