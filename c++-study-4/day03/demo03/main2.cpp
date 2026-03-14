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

    // 拷贝赋值运算符
    A& operator=(const A& a) {
        std::cout << "A& operator=(const A&)" << std::endl;

        // 防止自赋值
        if (this == &a) {
            return *this;
        }

        // 释放原有的内存空间
        if (m_pb != nullptr) {
            delete m_pb;
        }

        // 深拷贝（分配新的内存空间）
        m_pb = new B(*(a.m_pb));

        return *this;
    }

    // 移动赋值运算符（形参a通常是临时对象）
    // 建议移动赋值运算符重载函数都加上 noexcept 关键字，表示函数不会抛出任何异常，提高编译器的执行效率
    A& operator=(A&& a) noexcept {
        std::cout << "A& operator=(A&&)" << std::endl;

        // 防止自赋值
        if (this == &a) {
            return *this;
        }

        // 释放原有的内存空间
        if (m_pb != nullptr) {
            delete m_pb;
        }

        // 浅拷贝（不分配新的内存空间，直接转移临时对象的资源所有权）
        m_pb = a.m_pb;

        // 重置临时对象持有的m_pb指针
        a.m_pb = nullptr;

        return *this;
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
    std::cout << "======== test01() =======" << std::endl;

    A a;
    A a2;

    // 这种写法，编译器只会调用拷贝赋值运算符重载函数，而不会调用移动赋值运算符重载函数，会带来额外的资源拷贝开销
    // a2 = a;

    // 如果类 A 没有移动赋值运算符，那么编译器就会自动拷贝赋值运算符重载函数，会带来额外的资源拷贝开销
    // 如果类 A 有移动赋值运算符，那么编译器就会自动调用移动赋值运算符重载函数，将 a 对象的资源所有权转移给 a2 对象，不会调用拷贝赋值运算符重载函数，从而减少资源拷贝带来的开销
    // 特别注意，通过移动语义 std::move() 将 a 对象的资源所有权转移给 a2 对象后，后续都不能再使用 a 对象，因为 a 对象已经失去了资源所有权（即不再是一个完整的对象），建议后续都使用 a2 对象
    a2 = std::move(a);
}

int main() {
    test01();
    return 0;
}