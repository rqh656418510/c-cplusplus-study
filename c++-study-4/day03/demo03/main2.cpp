/**
 * 对象移动、移动构造函数、移动赋值运算符
 */

#include <iostream>

class B {
public:
    // 默认构造函数
    B(int bm = 0) : m_bm(bm) {
        std::cout << "B(int bm)" << std::endl;
    }

    // 拷贝构造函数
    B(const B& b) : m_bm(b.m_bm) {
        std::cout << "B(const B&)" << std::endl;
    }

    // 析构函数
    ~B() {
        std::cout << "~B()" << std::endl;
    }

private:
    int m_bm;
};

class A {
public:
    // 默认构造函数
    A() : m_pb(new B()) {
        std::cout << "A()" << std::endl;
    }

    // 拷贝构造函数
    A(const A& a) : m_pb(new B(*(a.m_pb))) {
        std::cout << "A(const A&)" << std::endl;
    }

    // 析构函数
    ~A() {
        std::cout << "~A()" << std::endl;
        delete m_pb;
    }

private:
    B* m_pb;
};

void test01() {
}

int main() {
    test01();
    return 0;
}