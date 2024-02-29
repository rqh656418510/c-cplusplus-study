/**
 * 1. extern 关键字浅析
 *
 * <p> 在 C++ 中使用 extern 关键字，可以解决 C++ 调用 C 语言函数的问题
 */

#include <iostream>
#include "sub.h"

using namespace std;

int main() {
    show();     // 默认情况下，这里无法直接调用在其他 C 语言源文件里定义的 show() 函数，即使是引入了 sub.h 头文件
    say();      // 默认情况下，这里无法直接调用在其他 C 语言源文件里定义的 say() 函数，即使是引入了 sub.h 头文件
    return 0;
}