/**
 * 类对象所占用的空间
 *
 * (c) 带静态成员变量的对象
 */

#include <iostream>

// 带静态成员变量的类
class A {

public:
    static int num;
};

int A::num = 0;

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 1
    return 0;
}