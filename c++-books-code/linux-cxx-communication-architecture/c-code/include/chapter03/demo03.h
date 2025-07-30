#include <stdio.h>

void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("收到了 SIGUSR1 信号!\n");
    } else if (signo == SIGUSR2) {
        printf("收到了 SIGUSR2 信号!\n");
    } else {
        printf("收到了未捕捉的信号\n");
    }
}

// 使用 signal() 函数来忽略或者捕捉信号
int chapter03_demo03_fun01() {
    // 注册信号处理函数
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("无法注册 SIGUSR1 信号的处理函数\n");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("无法注册 SIGUSR2 信号的处理函数\n");
    }

    for (;;) {
        sleep(1);
        printf("休息 1 秒\n");
    }
}