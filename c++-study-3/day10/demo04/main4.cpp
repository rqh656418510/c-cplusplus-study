/**
 * shared_ptr 的交叉引用（循环引用）问题
 */

#include <iostream>
#include <memory>

using namespace std;

// weak_ptr 智能指针访问资源

class B;    // 声明 B 的存在，但未定义 B

class A {

public:
    A() {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }

    // 声明 func 方法的存在，但未定义 func 方法
    void func();

    // 引用对象时，使用弱引用智能指针
    weak_ptr<B> _ptrB;

};

class B {

public:
    B() {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }

    // 声明 func 方法的存在，但未定义 func 方法
    void func();

    // 引用对象时，使用弱引用智能指针
    weak_ptr<A> _ptrA;
};

void A::func() {
    cout << "A::func()" << endl;
    // 必须将弱引用智能指针转换为强引用智能指针，这样才能访问被管理对象的资源
    shared_ptr<B> ptrB = _ptrB.lock();
    if (ptrB != nullptr) {
        ptrB->func();
    }
}

void B::func() {
    cout << "B::func()" << endl;
}

int main() {
    // 定义对象时，使用强引用智能指针
    shared_ptr<A> ptrA(new A());
    shared_ptr<B> ptrB(new B());

    // 这里不会造成智能指针循环引用的问题
    ptrA->_ptrB = ptrB;
    ptrA->func();
    ptrB->_ptrA = ptrA;

    // 打印智能指针的引用计数
    cout << ptrA.use_count() << endl;
    cout << ptrB.use_count() << endl;

    return 0;
}