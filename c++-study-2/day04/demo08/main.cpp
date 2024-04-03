/**
 * 常函数与常对象的使用
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        this->m_A = 0;
        this->m_B = 0;
    }

    // 定义常函数
    int getA() const {
        // 错误写法，常函数内不允许修改成员变量的值
        // this->m_A = 10;

        // 常函数内可修改被 mutable 修饰的成员变量的值
        this->m_B = 20;

        return this->m_A;
    }

    // 定义普通函数
    int getB() {
        return this->m_B;
    }

public:
    int m_A;
    mutable int m_B;
};

void test01() {
    Person p1;
    int m_A = p1.getA();
    cout << m_A << endl;
}

void test02() {
    // 定义常对象
    const Person p2;

    // 错误写法，不允许修改常对象的成员变量的值
    // p2.m_A = 10;

    // 错误写法，常对象不可以调用普通的成员函数
    // p2.getB();

    // 常对象可以调用常函数
    int m_A = p2.getA();
    cout << m_A << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
