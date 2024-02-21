/**
 * 1. C++ 中引用的注意事项
 */

#include <iostream>

using namespace std;

// 引用必须初始化
void test01() {
    // int &a;  必须初始化，否则编译不通过
    int b = 10;
    int c = 20;
    int &d = b;
    // int &d = c;  引用初始化后不可修改，否则编译不通过

}

// 引用必须是和一块合法的内存空间关联
void test02() {
    // int &a = 10;   引用必须是和一块合法的内存空间关联，否则编译不通过
}

// 函数的返回值是引用
int & hello() {
    int a = 10;
    // 返回局部变量的引用
    return a;
}

// 当函数的返回值是引用时，不要返回局部变量的引用，否则会出现意想不到的结果
void test03() {
    int &ref = hello();
    cout << "ref = " << ref << endl;    // 第一次正确打印值，是因为编译器做了优化
    cout << "ref = " << ref << endl;    // 第二次之后都无法正确打印值，会出现乱码现象
    cout << "ref = " << ref << endl;
    cout << "ref = " << ref << endl;
    cout << "ref = " << ref << endl;
}

// 函数的返回值是引用
int & bye() {
    static int a = 0;
    // 返回全局变量的引用
    return a;
}

// 当函数的返回值是引用时，这个函数调用可以作为左值
void test04() {
    bye() = 100;    // 相当于写了 a = 100
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}