/**
 * 1. C语言嵌套汇编代码
 */

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;

    __asm
    {
        mov a, 3        // 3的值放在a对应内存的位置
        mov b, 4        // 4的值放在a对应内存的位置
        mov eax, a      // 把a内存的值放在eax寄存器
        add eax, b      // eax和b相加，结果放在eax
        mov c, eax      // eax的值放在c中
    }

    printf("c = %d\n", c);
    return 0;
}