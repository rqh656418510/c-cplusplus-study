#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * 一个简单的 C 语言程序
 */
int chapter03_demo01_fun01() {
    for (;;) {
        sleep(1);
        printf("进程休息 1 秒\n");
    }

    printf("程序退出!\n");

    return 0;
}
