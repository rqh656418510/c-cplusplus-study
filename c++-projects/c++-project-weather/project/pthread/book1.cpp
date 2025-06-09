#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void EXIT(int signal) {
    printf("接收到 %d 信号，程序退出。\n", signal);
    // 正常退出程序
    exit(0);   
}

int main() {
    // 忽略所有信号，不希望程序被干扰
    for (int i=1; i<= 64; i++) {
        signal(i, SIG_IGN);
    }

    // 设置 ctrl + c、kill、killall 的处理函数
    signal(SIGINT, EXIT);
    signal(SIGTERM, EXIT);
    
    while (1) {
    	printf("执行了一次任务。\n");
	sleep(1);
    }
}
