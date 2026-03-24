/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (c) 虚继承
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

    void infoB() {
        cout << m_value_c << endl;
    }

public:
    int m_value_c;
};

int main() {
    return 0;
}