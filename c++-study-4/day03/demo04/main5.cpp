/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (e) 虚继承
 */

#include <iostream>

using namespace std;

// 虚基类
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

// 虚继承
class A : virtual Grand {
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

// 虚继承
class A2 : virtual public Grand {
public:
    A2(int i) : Grand(i), m_value_a2(i) {
        cout << "A2(int)" << endl;
    }

    virtual ~A2() {
        cout << "~A2()" << endl;
    }

    void info() {
        cout << m_value_a2 << endl;
    }

public:
    int m_value_a2;
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
class C : public A, public A2, public B {
public:
    // 这里需要手动调用虚基类（Grand）的构造函数
    C(int i, int j, int k) : Grand(i), A(i), A2(i), B(j), m_value_c(k) {
        cout << "C(int, int, int)" << endl;
    }

    virtual ~C() {
        cout << "~C()" << endl;
    }

    void infoA() {
        cout << m_value_c << endl;
    }

public:
    int m_value_c;
};

int main() {
    // 使用虚继承后，这里 Grand 类只会被构造一次
    C c1(10, 20, 30);

    // 使用虚继承后，这行代码可以编译成功，不存在二义性
    c1.m_value_grand = 20;

    return 0;
}