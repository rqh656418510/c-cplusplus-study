/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (b) 多重继承的使用
 */
#include <iostream>

using namespace std;

class Grand {
public:
    Grand(int i) : m_value_grand(i) {
        cout << "Grand(int)" << endl;
    }

    virtual ~Grand() {
        cout << "~Grand()" << endl;
    }

    void info() {
        cout << m_value_grand << endl;
    }

public:
    int m_value_grand;
};

// 单继承
class A : public Grand {
public:
    A(int i) : Grand(i), m_value_a(i) {
        cout << "A(int)" << endl;
    }

    virtual ~A() {
        cout << "~A()" << endl;
    }

    void info() {
        cout << m_value_a << endl;
    }

public:
    int m_value_a;
};

class B {
public:
    B(int i) : m_value_b(i) {
        cout << "B(int)" << endl;
    }

    virtual ~B() {
        cout << "~B()" << endl;
    }

    void info() {
        cout << m_value_b << endl;
    }

public:
    int m_value_b;
};

// 多重继承
class C : public A, public B {
public:
    C(int i, int j, int k) : A(i), B(j), m_value_c(k) {
        cout << "C(int, int, int)" << endl;
    }

    virtual ~C() {
        cout << "~C()" << endl;
    }

    void infoA() {
        // 在类的内部，显式调用父类 A 的 info() 函数
        A::info();
    }

    void infoB() {
        // 在类的内部，显式调用父类 B 的 info() 函数
        B::info();
    }

public:
    int m_value_c;
};

int main() {
    C c1(10, 20, 30);

    // c1.info();   // 编译失败，因为编译器不知道调用的式父类 A 还是父类 B 的 info() 函数，存在二义性
    c1.A::info();  // 编译通过，通过作用域，在类的外部，显式调用父类 A 的 info() 函数，输出 10

    c1.infoA();  // 输出 10
    c1.infoB();  // 输出 20

    return 0;
}