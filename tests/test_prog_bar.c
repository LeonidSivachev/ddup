#include <backup.h>
#include <signal.h>
#include <unistd.h>

void test_prog_bar()
{
  signal(SIGWINCH, sigwinch_handler);

  for (int i = 0; i <= 100; i += 5)
  {
    print_progress(i, 100);
    sleep(1);
  }
}
