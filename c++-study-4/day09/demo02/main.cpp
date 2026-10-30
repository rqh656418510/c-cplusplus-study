/**
 * 对象结构的发展和演化
 */

#include <iostream>

// 带虚函数的类
class A {
public:
    // 虚函数，增加虚函数表指针
    virtual void func() {
    }

};

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 8
    return 0;
}