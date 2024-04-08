/**
 * 加号运算符重载
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person(int a, int b) : m_A(a), m_B(b) {

    }

    // 使用成员函数重载加号运算符（二元运算符重载）
    Person operator+(Person &p) {
        Person newPerson(this->m_A + p.m_A, this->m_B + p.m_B);
        return newPerson;
    }

    // 声明友元函数
    friend Person operator-(Person &p1, Person &p2);

    int getA() const {
        return m_A;
    }

    int getB() const {
        return m_B;
    }

    void showPerson() {
        cout << "a = " << this->m_A << ", b = " << this->m_B << endl;
    }

private:
    int m_A;
    int m_B;

};

// 使用友元函数重载减号运算符（二元运算符重载）
Person operator-(Person &p1, Person &p2) {
    Person p(p1.m_A - p2.m_A, p1.m_B - p2.m_B);
    return p;
}

// 使用全局函数重载除号运算符（二元运算符重载）
Person operator/(Person &p1, Person &p2) {
    Person p(p1.getA() / p2.getA(), p1.getB() / p2.getB());
    return p;
}


int main() {
    Person p1(1, 3);
    Person p2(6, 9);

    // 重载加号运算符
    Person p3 = p1 + p2;
    p3.showPerson();

    // 重载减号运算符
    Person p4 = p2 - p1;
    p4.showPerson();

    // 重载除号运算符
    Person p5 = p2 / p1;
    p5.showPerson();
}
