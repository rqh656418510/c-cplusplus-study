/**
 * 类成员指针
 *
 * (c) 类成员函数指针 - 静态成员函数
 */

#include <iostream>

using namespace std;

class MyTest {
public:
    // 静态成员函数
    static void staticFunc(int i) {
        cout << "staticFunc(" << i << ")" << endl;
    }
};

int main() {
    // 声明一个类成员函数指针变量，其中 ptrStaticFunc 是变量名
    void (*ptrStaticFunc)(int);

    // 类成员函数指针变量初始化赋值
    ptrStaticFunc = &MyTest::staticFunc;

    // 直接调用类成员函数指针
    ptrStaticFunc(20);

    return 0;
}