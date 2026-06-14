#include <openssl/evp.h>

#include "backup.h"
#include "parse.h"

#define AUTHOR "Leonid Sivachev"

#define HASH_FUNC "MD5"

int main(int argc, char *argv[])
{
  parse(argc, argv);

  if (gconfig.verify)
  {
    unsigned char loader_md_value[EVP_MAX_MD_SIZE];
    unsigned char system_md_value[EVP_MAX_MD_SIZE];
    uint loader_md_len = 0;
    uint system_md_len = 0;

    backup_disk_verified(gconfig.loader_disk, gconfig.loader_img, HASH_FUNC,
                         loader_md_value, &loader_md_len);
    backup_disk_verified(gconfig.system_disk, gconfig.system_img, HASH_FUNC,
                         system_md_value, &system_md_len);

    printf("Loader digest is: ");
    for (uint i = 0; i < loader_md_len; i++)
      printf("%02x", loader_md_value[i]);
    printf("\n");

    printf("System digest is: ");
    for (uint i = 0; i < system_md_len; i++)
      printf("%02x", system_md_value[i]);
    printf("\n");
  }
  else
  {
    backup_disk(gconfig.loader_disk, gconfig.loader_img);
    backup_disk(gconfig.system_disk, gconfig.system_img);
  }

  return 0;
}
