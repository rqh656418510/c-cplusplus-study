/**
 * 指向类成员的指针
 */

#include <iostream>

using namespace std;

class Test {

public:
    void func() {
        cout << "call Test:: func" << endl;
    }

    static void static_func() {
        cout << "call Test::static_func" << endl;
    }

    int ma;

    static int mb;

};

// 初始化类成员静态变量
int Test::mb = 50;

void test01() {
    Test t1;    // 栈上分配内存
    Test *t2 = new Test();  // 堆上分配内存

    // 错误写法
    // int * p = &Test::ma;

    // 指向类成员变量的指针
    int Test::*p = &Test::ma;

    // 通过指针访问类成员变量
    t1.*p = 20;
    cout << t1.ma << ", " << t1.*p << endl;

    // 通过指针访问类成员变量
    t2->*p = 30;
    cout << t2->ma << ", " << t2->*p << endl;

    delete t2;
}

void test02() {
    // 正确写法, 指向类成员静态变量的指针
    int *p1 = &Test::mb;

    // 通过指针访问类成员静态变量
    *p1 = 60;
    cout << Test::mb << ", " << *p1 << endl;
}

void test03() {
    Test t1;    // 栈上分配内存
    Test *t2 = new Test();  // 堆上分配内存

    // 错误写法
    // void (*pFunc)() = &Test::func;

    // 指向类成员函数的指针（函数指针）
    void (Test::*pFunc)() = &Test::func;

    // 通过指针调用类成员函数
    (t1.*pFunc)();

    // 通过指针调用类成员函数
    (t2->*pFunc)();
}

void test04() {
    // 正确写法, 指向类成员静态函数的指针（函数指针）
    void (*pStaticFunc)() = &Test::static_func;

    // 通过指针调用类成员静态函数
    (*pStaticFunc)();
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}