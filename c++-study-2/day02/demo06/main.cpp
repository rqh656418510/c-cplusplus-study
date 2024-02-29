/**
 * 1. extern 浅析
 */

#include <iostream>

// 在 C++ 中调用其他 C 语言源文件里的函数
// 下述代码的作用是让编译器按照 C 语言的方式做链接
extern "C" void show();

using namespace std;

int main() {
    show();
    return 0;
}