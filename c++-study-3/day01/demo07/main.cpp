/**
 * 掌握const和一二级指针的结合应用
 */

#include <iostream>

using namespace std;

/**
 * const与一级指针的结合
 */
void test01() {
    const int a = 10;
    // int *p = &a; // 错误写法，不能将常量的地址泄漏给一个普通的指针或者普通的引用变量
}

/**
 * const与一级指针的结合
 * <p> C++的语言规范：const 修饰的是离它最近的类型
 * <p> const 在 * 的左边则定值，const 在 * 的右边则定向，即左定值右定向
 */
void test02() {
    int a = 10;
    int b = 20;

    // 第一种写法（左定值）
    const int *p = &a;
    p = &b; // 正确写法，可以任意指向不同的int类型的内存
    // *p = 30; // 错误写法，不能通过指针间接修改指向的内存的值
    cout << "p = " << *p << endl; // p = 20

    // 第一种写法的变体（左定值）
    int const *p2 = &a;
    p2 = &b; // 正确写法，可以任意指向不同的int类型的内存
    // *p2 = 30; // 错误写法，不能通过指针间接修改指向的内存的值
    cout << "p2 = " << *p2 << endl; // p2 = 20

    // 第二种写法（右定向）
    int *const p3 = &a;
    // p3 = &b; // 错误写法，不可以任意指向不同的int类型的内存
    *p3 = 30; // 正确写法，可以通过指针间接修改指向的内存的值
    cout << "p3 = " << *p3 << ", a = " << a << endl; // p3 = 30, a = 30
}

/**
 * const与二级指针的结合
 */
void test03() {
    int a = 10;
    int *p = &a;

    // 第一种写法
    // const int **q = &p;  // 错误写法

    // 第二种写法
    int *const *q = &p;  // 正确写法

    // 第三种写法
    // int **const q = &p;  // 错误写法
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
