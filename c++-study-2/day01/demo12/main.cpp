/**
 * 1. C++ 中的常量引用
 */

#include <iostream>

using namespace std;

// 常量引用的使用
void test01() {
    // 常量
    const int b = 10;
    printf("b = %d\n", b);

    // 引用必须是和一块合法的内存空间关联，若不加const关键字，则编译失败
    // int &a = 19;

    // 常量引用
    const int &a = 19;

    cout << "a = " << a << endl;
}

// 使用字面量常量对常量引用初始化后，将生成一个只读变量，但可以使用指针的方式更改常量引用的值
void test02() {
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

// 使用常量引用修饰形参
void showValue(const int &val) {
    // val = 10;    无法直接更改形参的值，编译会不通过
    cout << "val = " << val << endl;
}

void test03() {
    int a = 3;
    showValue(a);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}