/**
 * 1. system()函数的使用
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    system("ls -al");      // Linux 平台
    // system("calc");              // Windows 平台
    return 0;
}