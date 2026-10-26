/**
 * 类对象所占用的空间
 *
 * (d) 带非静态成员变量的对象
 */

#include <iostream>

// 带非静态成员变量的类
class A {

public:
    int num;
};

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 4
    return 0;
}