/**
 * 再谈动态绑定
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base(int data = 0) : ma(data) {

    }

    virtual void show() {
        cout << "Base::show()" << endl;
    }

protected:
    int ma;

};

class Device : public Base {

public:
    Device(int data = 0) : Base(data), mb(data) {

    }

    void show() {
        cout << "Device::show()" << endl;
    }

private :
    int mb;

};

int main() {
    Base base;
    Device device;

    cout << "=====================" << endl;

    base.show();    // 静态绑定
    device.show();  // 静态绑定

    cout << "=====================" << endl;

    Base *bptr1 = &base;
    bptr1->show();   // 动态绑定（必须由指针或者引用调用虚函数）

    Base *bptr2 = &device;
    bptr2->show();   // 动态绑定（必须由指针或者引用调用虚函数）

    Base &b1 = base;
    base.show();     // 动态绑定（必须由指针或者引用调用虚函数）

    Base &b2 = device;
    b2.show();       // 动态绑定（必须由指针或者引用调用虚函数）

    cout << "=====================" << endl;

    Device *dptr = &device;
    dptr->show();   // 动态绑定（虚函数通过指针或者引用变量调用，才会发生动态绑定）

    Device &d = device;
    d.show();       // 动态绑定（虚函数通过指针或者引用变量调用，才会发生动态绑定）

    Device *dptr2 = (Device *) &base;   // 强制类型转换（不安全）
    dptr2->show();   // 动态绑定

    return 0;
}