/**
 * 重载、重写、隐藏
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base(int data = 10) : ma(data) {

    }

    void show() {
        cout << "Base::show()" << endl;
    }

    void show(int a) {
        cout << "Base::show(int)" << endl;
    }

private :
    int ma;

};

class Device : public Base {

public:
    Device(int data = 20) : Base(data), mb(data) {

    }

    void show() {
        cout << "Device::show()" << endl;
    }

private:
    int mb;

};

void test01() {
    cout << "=========== test01() ===========" << endl;
    Device device;
    device.show();
    // device.show(20);         // 错误写法，派生类的 show() 函数将基类的 show(int a) 函数隐藏了，无法正常调用基类的同名函数
    device.Base::show(20);   // 正确写法，派生类加上作用域可以正常调用基类的同名函数
}

void test02() {
    cout << "=========== test02() ===========" << endl;
    Base base;
    Device device;
    base = device;      // 正确写法，类型从下到上的转换
    // device = base;   // 错误写法，类型从上到下的转换
    base.show();
    base.show(30);
}

void test03() {
    cout << "=========== test03() ===========" << endl;
    Base base;
    Device device;

    Base *_base = &device;          // 正确写法，类型从下到上的转换
    // Device *_device = &base;     // 错误写法，类型从上到下的转换
    _base->show();
    _base->show(40);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
