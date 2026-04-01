/**
 * 类成员指针
 *
 * (a) 类成员函数指针 - 普通成员函数
 */

#include <iostream>

using namespace std;

class MyTest {
public:
    // 普通成员函数
    void commonFunc(int i) {
        cout << "commonFunc(" << i << ")" << endl;
    }
};

int main() {
    // 声明一个类成员函数指针变量，其中 ptrCommonFunc 是变量名
    void (MyTest::*ptrCommonFunc)(int);

    // 类成员函数指针变量初始化赋值
    ptrCommonFunc = &MyTest::commonFunc;

    MyTest t1, *ptr1;
    ptr1 = &t1;

    // 通过对象本身调用类成员函数指针
    (t1.*ptrCommonFunc)(10);

    // 通过对象指针调用类成员函数指针
    (ptr1->*ptrCommonFunc)(20);

    return 0;
}