/**
 * 左移运算符重载
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        this->m_A = 0;
        this->m_B = 0;
    }

    Person(int a, int b) {
        this->m_A = a;
        this->m_B = b;
    }

    // 声明友元函数
    friend ostream &operator<<(ostream &out, Person &p);

private:
    int m_A;
    int m_B;

};

// 使用友元函数重载左移运算符
ostream &operator<<(ostream &out, Person &p) {
    out << "a = " << p.m_A << ", b = " << p.m_B << endl;
    return out;
}

int main() {
    Person p(1, 2);
    // 重载左移运算符
    cout << p << endl;
}
