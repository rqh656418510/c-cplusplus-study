/**
 * 1. C++中的引用之常量引用（使用字面量常量初始化 const 引用）
 */

#include <iostream>

using namespace std;

int main() {
    const int b = 10;
    printf("b = %d\n", b);

    // int &a = 19; 引用必须是和一块合法的内存空间关联，若不加const关键字，则编译失败

    const int &a = 19;
    printf("a = %d \n", a);
    return 0;
}