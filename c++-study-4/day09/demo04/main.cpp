/**
 * this指针调整
 */

#include <iostream>

// 基类 A
class A {
public:
    A() {
        std::cout << "A::A() this ptr is " << this << std::endl;
    }

    void funcA() {
        std::cout << "A::funcA() this ptr is " << this << std::endl;
    }

public:
    int a;
};

// 基类 B
class B {
public:
    B() {
        std::cout << "B::B() this ptr is " << this << std::endl;
    }

    void funcB() {
        std::cout << "B::funcB() this ptr is " << this << std::endl;
    }

public:
    int b;
};

// 派生类 C（多重继承）
class C : public A, public B {
public:
    C() {
        std::cout << "C::C() this ptr is " << this << std::endl;
    }

    void funcC() {
        std::cout << "C::funcC() this ptr is " << this << std::endl;
    }

public:
    int c;
};

int main() {
    std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
    std::cout << "sizeof(B) = " << sizeof(B) << std::endl;
    std::cout << "sizeof(C) = " << sizeof(C) << std::endl;

    C c;
    c.funcA();
    c.funcB();
    c.funcC();

    return 0;
}