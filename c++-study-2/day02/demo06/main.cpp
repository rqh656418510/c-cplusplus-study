/**
 * 1. extern 浅析
 */

#include <iostream>
#include "sub.h"

using namespace std;

int main() {
    show();     // 默认情况下，这里无法直接调用在其他 C 语言源文件里定义的 show() 函数，即使是引入了 sub.h 头文件
    say();      // 默认情况下，这里无法直接调用在其他 C 语言源文件里定义的 say() 函数，即使是引入了 sub.h 头文件
    return 0;
}