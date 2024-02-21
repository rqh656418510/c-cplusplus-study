/**
 * 1. C++ 中的常量引用
 */

#include <iostream>

using namespace std;

// 常量引用的使用
void test01() {

    // 引用必须是和一块合法的内存空间关联，若不加const关键字，则编译失败
    // int &a = 19;

    // 常量引用
    const int &a = 19;

    cout << "a = " << a << endl;
}

// 使用普通变量初始化常量引用
void test02() {
    int a = 10;

    // 使用普通变量初始化常量引用
    const int &b = a;

    // b = 11;  错误写法，这里不能通过引用改变 a 的值，无法通过编译

    // 可以使用指针的方式更改常量引用的值
    int *p = (int *) &b;
    *p = 12;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

// 使用字面量常量对常量引用初始化后，将生成一个只读变量，但可以使用指针的方式更改常量引用的值
void test03() {
    // 使用字面量常量对常量引用初始化
    const int &a = 10;

    // 常量引用为只读，不能直接更改值
    // a = 20;

    // 可以使用指针的方式更改常量引用的值
    int *p = (int *) &a;
    *p = 20;
    cout << "a = " << a << endl;
    cout << "*p = " << *p << endl;
}

// 函数参数是常量引用
void showValue(const int &val) {
    // 无法直接更改形参的值，编译会不通过
    // val = 10;

    // 但可以使用指针的方式更改形参的值
    int *p = (int *) &val;
    *p = 30;
}

void test04() {
    int a = 10;
    showValue(a);
    cout << "a = " << a << endl;
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}