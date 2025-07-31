/**
 * 演示错用 malloc（为不可重入函数）为可重入函数的后果
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 信号处理函数
void sig_usr_2(int signo) {
    if (signo == SIGUSR1) {
        printf("收到了 SIGUSR1 信号!\n");
    } else if (signo == SIGUSR2) {
        printf("收到了 SIGUSR2 信号!\n");
    } else {
        printf("收到了未捕捉的信号\n");
    }
}

// 演示错用 malloc（为不可重入函数）为可重入函数的后果
int chapter03_demo04_fun01() {
    // 注册信号处理函数
    if (signal(SIGUSR1, sig_usr_2) == SIG_ERR) {
        printf("无法注册 SIGUSR1 信号的处理函数\n");
    }
    if (signal(SIGUSR2, sig_usr_2) == SIG_ERR) {
        printf("无法注册 SIGUSR2 信号的处理函数\n");
    }

    for (;;) {
        sleep(1);
        printf("休息 1 秒\n");
    }
}