/**
 * 虚析构函数
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base(int data) : ma(data) {
        cout << "Base()" << endl;
    }

    // 虚析构函数
    virtual ~Base() {
        cout << "~Base()" << endl;
    }

    // 虚函数
    virtual void show() {
        cout << "Base::show()" << endl;
    }

private :
    int ma;

};

class Device : public Base {

public:
    Device(int data) : Base(data), mb(data) {
        cout << "Device()" << endl;
    }

    // 当基类的析构函数是 virtual 虚函数，那么派生类的析构函数会自动成为虚函数
    ~Device() {
        cout << "~Device()" << endl;
    }

private:
    int mb;

};

int main() {
    Base *pb = new Device(10);
    pb->show();
    delete pb;

    return 0;
}
