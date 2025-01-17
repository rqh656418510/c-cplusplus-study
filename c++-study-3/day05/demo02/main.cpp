/**
 * 派生类的构造过程
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base(int data) : ma(data) {
        cout << "Base()" << endl;
    }

    ~Base() {
        cout << "~Base()" << endl;
    }

protected:
    int ma;

};

class Device : public Base {

public:
    // 显式调用 Base 的构造函数初始化 ma
    Device(int data) : Base(data), mb(data) {
        cout << "Device()" << endl;
    }

    ~Device() {
        cout << "~Device()" << endl;
    }

private:
    int mb;

};

int main() {
    Device d(2);    // 先构造的后析构，即后构造的先析构
    return 0;
}
