/**
 * 类对象所占用的空间
 *
 * (b) 带成员函数的对象
 */

#include <iostream>

// 带成员函数的类
class A {

public:
    void func1() {
    }

    void func2() {
    }

    void func3() {
    }
};

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 1
    return 0;
}