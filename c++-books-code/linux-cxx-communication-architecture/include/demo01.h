#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int demo01_test01() {
  for (;;) {
    sleep(1);
    printf("进程休息 1 秒\n");
  }

  printf("程序退出!\n");

  return 0;
}
