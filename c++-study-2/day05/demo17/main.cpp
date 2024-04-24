/**
 * 多继承的概念以及问题
 */

#include <iostream>

using namespace std;

class Base1 {

public:
    Base1(int a) {
        this->m_A = a;
    }

public:
    int m_A;

};

class Base2 {

public:
    Base2(int a) {
        this->m_A = a;
    }

public:
    int m_A;

};

// 多继承
class Son : public Base1, public Base2 {

public:
    Son(int a, int b) : Base1(a), Base2(a) {
        this->m_B = b;
    }

public :
    int m_B;

};

void test01() {
    cout << sizeof(Son) << endl;
}

void test02() {
    Son son(1, 2);
    cout << son.m_B << endl;

    // 解决多继承中的二义性问题
    cout << son.Base1::m_A << endl;
    cout << son.Base2::m_A << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
