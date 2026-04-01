/**
 * 类成员指针
 *
 * (b) 类成员函数指针 - 虚函数
 */

#include <iostream>

using namespace std;

class MyTest {
public:
    // 虚函数
    virtual void virtualFunc(int i) {
        cout << "virtualFunc(" << i << ")" << endl;
    }
};

int main() {
    // 声明一个类成员函数指针变量，其中 ptrVirtualFunc 是变量名
    void (MyTest::*ptrVirtualFunc)(int);

    // 类成员函数指针变量初始化赋值
    ptrVirtualFunc = &MyTest::virtualFunc;

    MyTest t1, *ptr1;
    ptr1 = &t1;

    // 通过对象本身调用类成员函数指针
    (t1.*ptrVirtualFunc)(10);

    // 通过对象指针调用类成员函数指针
    (ptr1->*ptrVirtualFunc)(20);

    return 0;
}