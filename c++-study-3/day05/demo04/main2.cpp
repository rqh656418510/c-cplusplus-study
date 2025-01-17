/**
 * 虚函数、动态绑定和动态绑定
 *
 * <p> 动态绑定（使用虚函数）
 */

#include <iostream>
#include <typeinfo>

using namespace std;

class Base {

public:
    Base(int data = 10) : ma(data) {

    }

    // 虚函数
    virtual void show() {
        cout << "Base::show()" << endl;
    }

    // 虚函数
    virtual void show(int num) {
        cout << "Base::show(int num)" << endl;
    }

private:
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

int main() {
    Device device(50);

    Base *pb = &device;
    pb->show();           // 动态（运行时期）绑定（函数的调用）
    pb->show(20);    // 动态（运行时期）绑定（函数的调用）

    cout << sizeof(Base) << endl;
    cout << sizeof(Device) << endl;

    cout << typeid(pb).name() << endl;      // class Base *
    cout << typeid(*pb).name() << endl;     // class Devic e

    return 0;
}
