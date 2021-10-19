/**
 * 1. C++中的引用之常引用（综合案例）
 */

#include <iostream>

using namespace std;

int main() {
    // 普通引用
    int a = 10;
    int &b = a;

    // 常量引用，让变量拥有只读属性
    const int &c = a;

    // 常量引用的初始化分为以下两种

    // 1.用变量初始化常量引用
    {
        int x = 20;
        const int &y = x;
        printf("y:%d \n", y);
    }

    // 2.用常量初始化常量引用
    {
        // int &m = 10;  // 错误写法，引用是内存空间的别名，字面量10没有内存空间，没有方法做引用
        const int &m = 10;
    }
    return 0;
}