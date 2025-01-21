/**
 * 理解虚基类和虚继承
 */

#include <iostream>

using namespace std;

// 虚基类（被虚继承的类称为虚基类）
class A {

public:
    virtual void show() {
        cout << "call A::show()" << endl;
    }

private:
    int ma;

};

// 虚继承
class B : virtual public A {

public:
    void show() {
        cout << "call B::show()" << endl;
    }

private :
    int mb;

};

int main() {
    cout << "size : " << sizeof(B) << endl;

    // A *a = new B();
    // a->show();       // 正常调用，发生动态绑定
    // delete a;        // 调用失败，异常终止执行

    B b;
    A &a = b;   // 正常调用，发生动态绑定
    b.show();

    return 0;
}
