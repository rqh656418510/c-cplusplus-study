/**
 * 构造函数的初始化列表
 */

#include <iostream>

using namespace std;

class Person {

public:

    // 初始化列表使用
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c) {

    }

    // 初始化列表结合函数默认参数使用
    Person(int a = 2, int b = 4) : m_A(a), m_B(b), m_C(6) {

    }

    int getA() const {
        return m_A;
    }

    int &getB() const {
        return m_B;
    }

    const int getC() const {
        return m_C;
    }

private:
    int m_A;
    int &m_B;
    const int m_C;
};

int main() {
    Person p1(1, 2, 3);
    printf("a = %d, b = %d, c = %d\n", p1.getA(), p1.getB(), p1.getC());

    Person p2;
    printf("a = %d, b = %d, c = %d\n", p2.getA(), p2.getB(), p2.getC());

    return 0;
}
