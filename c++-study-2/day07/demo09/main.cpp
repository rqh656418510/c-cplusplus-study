/**
 * 类模板碰到继承的问题以及解决
 *
 * <p> 类模板可以被普通类继承，普通类继承类模板时，需要声明父类具体的数据类型。
 * <p> 在 C++ 中，类模板可以继承类模板。
 */

#include <iostream>

using namespace std;

// 类模板声明
template<class T>
class Base {

public:

    Base(T a) {
        this->m_A = a;
    }

    T &getA() {
        return this->m_A;
    }

public:
    T m_A;

};

// 普通类继承类模板，需要声明具体的类型（模板参数列表），这里的 <int> 不能省略
class Child1 : public Base<int> {

public:
    Child1(int a, int b) : Base<int>(a) {
        this->m_B = b;
    }

    void print() {
        cout << "a = " << this->m_A << ", b = " << this->m_B << endl;
    }

public :
    int m_B;

};

void test01() {
    Base<int> base(3);
    cout << "a = " << base.getA() << endl;

    Child1 child1(5, 6);
    child1.print();
}

// 类模板继承类模板
template<class T1, class T2>
class Child2 : public Base<T2> {

public:
    Child2(int a, int c) : Base<T2>(a) {
        this->m_C = c;
    }

    void print() {
        cout << "a = " << this->m_A << ", c = " << this->m_C << endl;
    }

public:
    T1 m_C;

};

void test02() {
    Base<int> base(7);
    cout << "a = " << base.getA() << endl;

    Child2<int, int> child2(8, 9);
    child2.print();
}


int main() {
    test01();
    test02();
    return 0;
}
