/**
 * shared_ptr 的交叉引用（循环引用）问题
 */

#include <iostream>
#include <memory>

using namespace std;

// 模拟 shared_ptr 智能指针发生循环引用问题

class B;

class A {

public:
    A() {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }

    shared_ptr<B> _ptrB;

};

class B {

public:
    B() {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }

    shared_ptr<A> _ptrA;
};

int main() {
    shared_ptr<A> ptrA(new A());
    shared_ptr<B> ptrB(new B());

    // 这里会造成智能指针的循环引用，导致程序结束运行后资源无法正常被释放
    ptrA->_ptrB = ptrB;
    ptrB->_ptrA = ptrA;

    // 打印智能指针的引用计数
    cout << ptrA.use_count() << endl;
    cout << ptrB.use_count() << endl;

    return 0;
}