/**
 * 1. C++中的函数重载与函数指针
 */

#include <iostream>
#include <string.h>

using namespace std;

int func(int x) {
    return x;
}

int func(int a, int b) {
    return a + b;
}

int func(const char *s) {
    return strlen(s);
}

// 第一种写法：声明函数类型
typedef int (FUNC)(int a);

// 第二种写法：声明函数指针类型
typedef int(*PFUNC)(int a, int b);

int main() {
    // 根据上面的第一种写法，定义函数指针类型的变量
    FUNC *FUNC = func;
    int c = FUNC(1);
    printf("c = %d\n", c);

    // 根据上面的第二种写法，定义函数指针类型的变量
    PFUNC p = func;
    int d = p(3, 4);
    printf("d = %d\n", d);
    return 0;
}