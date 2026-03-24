/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (d) 多重继承 - 从多个基类继承构造函数
 */

#include <iostream>

using namespace std;

class A {
public:
    A(int i) {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }
};

class B {
public:
    B(int i) {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }
};

class C : public A, public B {
public:
    // 继承 A 类的全部有参构造函数，除了 A 类的默认构造函数、默认拷贝构造函数、默认移动构造函数（如果存在）
    using A::A;

    // 继承 B 类的全部有参构造函数，除了 B 类的默认构造函数、默认拷贝构造函数、默认移动构造函数（如果存在）
    using B::B;

    // 如果派生类从它的多个基类中继承了相同参数的构造函数，那么这个派生类必须为该构造函数显式定义自己的版本，否则会有二义性，导致编译失败
    C(int i) : A(i), B(i) {
    }
};

int main() {
    C c1(10);
    return 0;
}