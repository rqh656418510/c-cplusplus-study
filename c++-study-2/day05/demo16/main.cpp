/**
 * 继承中的静态成员处理
 */

#include <iostream>

using namespace std;

class Base {

public:
    static void func() {
        cout << "Base.func()" << endl;
    }

public:
    static int m_A;

};

int Base::m_A = 10;

class Son : public Base {

public:
    static void func() {
        cout << "Son.func()" << endl;
    }

public:
    static int m_A;

};

int Son::m_A = 20;

void test01() {
    // 访问父类的静态成员属性
    cout << Base::m_A << endl;

    // 访问子类的静态成员属性
    cout << Son::m_A << endl;
}

void test02() {
    // 访问父类的静态成员函数
    Base::func();
    Son::Base::func();

    // 访问子类的静态成员函数
    Son::func();
}

int main() {
    test01();
    test02();
    return 0;
}
