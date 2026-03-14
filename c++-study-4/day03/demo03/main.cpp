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
    // 建议移动构造函数都加上 noexcept 关键字，表示函数不会抛出任何异常，提高编译器的执行效率
    A(A&& a) noexcept : m_pb(a.m_pb) {
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

    // 如果类 A 有移动构造函数，那么编译器就会自动调用移动构造函数，将临时对象的资源所有权转移给 a 对象，从而减少资源拷贝带来的开销
    A a = getA();
}

void test03() {
    std::cout << "======== test03() =======" << std::endl;

    // 如果类 A 有移动构造函数，那么编译器就会自动调用移动构造函数，将临时对象的资源所有权转移给 a 对象，从而减少资源拷贝带来的开销
    A a = getA();

    // 这样写法，不会调用移动构造函数，也就是不会创建新的对象，不会发生资源所有权转移，仅仅是将左值强制转换为右值，并绑定到右值引用，效果等同于 a 对象有了一个新的别名叫 ref
    // A &&ref = std::move(a);

    // 使用移动语义 std::move()，将左值强制转换为右值，这样编译器就会调用移动构造函数，而不是调用拷贝构造函数，也就是将 a 对象的资源所有权转移给 a2 对象，从而减少资源拷贝带来的开销
    // 特别注意，通过移动语义 std::move() 将 a 对象的资源所有权转移给 a2 对象后，后续都不能再使用 a 对象，因为 a 对象已经失去了资源所有权（即不再是一个完整的对象），建议后续都使用 a2 对象
    A a2 = std::move(a);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}