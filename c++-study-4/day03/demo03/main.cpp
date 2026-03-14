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

    // 虚析构函数
    virtual ~B() {
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

    // 移动构造函数（形参a通常是临时对象）
    A(A&& a) : m_pb(a.m_pb) {
        // 重置临时对象持有的m_pb指针
        a.m_pb = nullptr;
        std::cout << "A(A &&)" << std::endl;
    }

    // 拷贝构造函数
    A(const A& a) : m_pb(new B(*(a.m_pb))) {
        std::cout << "A(const A&)" << std::endl;
    }

    // 虚析构函数
    virtual ~A() {
        std::cout << "~A()" << std::endl;
        delete m_pb;
    }

private:
    B* m_pb;
};

static A getA() {
    A tmp;       // 临时对象
    return tmp;  // 返回临时对象
}

void test01() {
    std::cout << "======== test01() =======" << std::endl;
    B* pb = new B();      // 调用构造函数
    B* pb2 = new B(*pb);  // 调用拷贝构造函数
    delete pb;
    delete pb2;
}

void test02() {
    std::cout << "======== test02() =======" << std::endl;
    A a = getA();  // 如果类 A 有移动构造函数，那么就会调用移动构造函数，将临时对象的资源所有权转移给 a 对象
}

int main() {
    test01();
    test02();
    return 0;
}