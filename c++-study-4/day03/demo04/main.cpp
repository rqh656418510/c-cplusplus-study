/**
 * 继承的构造函数、多重继承、虚继承
 */

#include <iostream>

using namespace std;

class A {
public:
    A(int i, int j) {
    }

    A(int i, int j, int k) {
    }
};

class B : public A {
public:
    // 继承 A 类的全部有参构造函数，除了 A 类的默认构造函数、默认拷贝构造函数、默认移动构造函数（如果存在）
    using A::A;
};

int main() {
    B b1(1, 2);     // 编译通过
    B b2(1, 2, 3);  // 编译通过
    // B b3;        // 编译失败，因为 A 类没有默认构造函数，编译器也就不会为 B 类自动生成默认构造函数
    return 0;
}