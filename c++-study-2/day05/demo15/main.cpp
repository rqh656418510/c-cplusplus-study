/**
 * 继承中的同名成员处理
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base() {
        this->m_A = 100;
    }

    void print() {
        cout << m_A << endl;
    }

public:
    int m_A;

};

class Son : public Base {

public:
    Son() {
        this->m_A = 200;
    }

    void print() {
        cout << m_A << endl;
    }

public:
    int m_A;

};

void test01() {
    Son son;
    cout << son.m_A << endl;
    // 继承中同名变量的处理，访问父类的成员属性
    cout << son.Base::m_A << endl;
}

void test02() {
    Son son;
    son.print();
    // 继承中同名函数的处理，访问父类的成员函数
    son.Base::print();
}

int main() {
    test01();
    cout << "----------" << endl;
    test02();
    return 0;
}
