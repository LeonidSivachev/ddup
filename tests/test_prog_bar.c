#include <backup.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define TEST_FREQ 5

void test_prog_bar()
{
  signal(SIGWINCH, sigwinch_handler);

  printf("First copying...\n");
  for (int i = 0; i <= 100; i += TEST_FREQ)
  {
    print_progress(i, 100);
    sleep(1);
  }
  printf("First copying completed.\n");

  printf("Second copying...\n");
  for (int i = 0; i <= 100; i += TEST_FREQ)
  {
    print_progress(i, 100);
    sleep(1);
  }
  printf("Second copying completed.\n");
}
