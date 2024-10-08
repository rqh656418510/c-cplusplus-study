#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handler(int signal) {
    printf("程序接收到 %d 信号。\n");
}

void alarmfunc(int signal) {
    printf("接收到时钟信号%d。\n", signal);
}

int main() {
    for (int i=0; i<=64; i++) {
    	signal(i, handler);
    }

    // 忽略指定的信号
    signal(15, SIG_IGN);

    // 还原指定的信号
    signal(15, SIG_DFL);

    // 处理时钟信号
    signal(SIGALRM, alarmfunc);

    // 定时发出时钟信号
    alarm(3);

    while (1) {
    	printf("执行了一次任务。\n");
	sleep(1);
    }
}
