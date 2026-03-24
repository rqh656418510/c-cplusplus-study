/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (b) 多重继承
 */

#include <iostream>

using namespace std;

class Grand {
public:
    Grand(int i) : m_value_grand(i) {
    }

    virtual ~Grand() {
    }

    void info() {
        cout << m_value_grand << endl;
    }

public:
    int m_value_grand;
    static int m_value_static;  // 声明静态成员变量
};

// 定义类外初始化静态成员变量
int Grand::m_value_static = 5;

// 单继承
class A : public Grand {
public:
    A(int i) : Grand(i), m_value_a(i) {
    }

    virtual ~A() {
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
    }

    virtual ~B() {
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
    }

    virtual ~C() {
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

void test01() {
    cout << "============test01()===========" << endl;

    C c1(10, 20, 30);

    // c1.info();   // 编译失败，因为编译器不知道调用的式父类 A 还是父类 B 的 info() 函数，存在二义性
    c1.A::info();  // 编译通过，通过作用域，在类的外部，显式调用父类 A 的 info() 函数，输出 10

    c1.infoA();  // 输出 10
    c1.infoB();  // 输出 20
}

void test02() {
    cout << "============test02()===========" << endl;

    A a1(6);
    A::m_value_static = 15;
    cout << A::m_value_static << endl;
    cout << C::m_value_static << endl;
}

int main() {
    test01();
    test02();
    return 0;
}