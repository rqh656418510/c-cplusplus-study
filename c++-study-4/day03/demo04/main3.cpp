/**
 * 继承的构造函数、多重继承、虚继承
 *
 * (b) 多重继承 - 静态变量
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

// 类外定义静态成员变量
int Grand::m_value_static = 2;

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
        cout << m_value_c << endl;
    }

public:
    int m_value_c;
};

int main() {
    // static 变量属于类，在继承体系中只有一份，父类修改后，子类访问到的一定是修改后的值（不存在子类自己拥有 static 副本的说法）
    A::m_value_static = 15;
    cout << A::m_value_static << endl;
    cout << C::m_value_static << endl;
    return 0;
}