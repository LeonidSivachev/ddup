#include <backup.h>
#include <unistd.h>

void test_prog_bar()
{
  for(int i = 0; i <= 100; i += 5)
  {
    print_progress(i, 100);
    sleep(1);
  }
}
