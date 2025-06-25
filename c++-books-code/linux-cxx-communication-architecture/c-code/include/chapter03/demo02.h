
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Fork 子进程，并创建新的会话，实现 bash 进程关闭后，其他应用进程也不会被关闭
 */
int chapter03_demo02_fun01() {
    // SIG_IGN 表示要忽略该信号，请求操作系统不要执行对应信号的默认处理动作（杀死进程）
    // signal(SIGHUP, SIG_IGN);

    // 如果主进程是进程组的组长，不允许调用 setsid() 来创建新的会话
    // setsid();

    __pid_t pid;

    // Fork 子进程，子进程会在 fork()
    // 函数调用之后开始执行，原来的父进程也会继续往下执行（即父子线程是并行运行的）
    pid = fork();

    if (pid < 0) {
        printf("fork 子进程出错!\n");
    } else if (pid == 0) {
        // 子进程才会执行到这里
        printf("子进程开始执行!\n");

        // 创建新的会话（Session）
        setsid();

        for (;;) {
            sleep(1);
            printf("子进程休息 1 秒\n");
        }

        return 0;
    } else {
        // 父进程才会执行到这里
        for (;;) {
            sleep(1);
            printf("父进程休息 1 秒\n");
        }

        return 0;
    }

    printf("程序退出!\n");

    return 0;
}