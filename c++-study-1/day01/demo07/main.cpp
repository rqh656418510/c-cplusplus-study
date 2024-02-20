/**
 * 1. C++中的引用
 */

#include <iostream>

using namespace std;

void demo1() {
    int a = 10;  //编译器分配4个字节内存，a是内存空间的别名
    int &b = a;  // b就是a的别名，即b引用了a
    a = 11;      //直接赋值
    {
        int *p = &a;
        *p = 12;
        printf("a = %d \n", a);
    }
    b = 14;
    printf("a = %d, b = %d", a, b);
}

int main() {
    demo1();
}
