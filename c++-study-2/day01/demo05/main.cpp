/**
 * 1. C++ 对 const 关键字的增强
 */

#include <iostream>

using namespace std;

// 全局的常量，受到保护，不允许更改值
const int m_A = 10;

// 第一种情况
void test01() {
    // 局部的常量，编译器不会分配内存空间，无法通过指针更改值
    const int m_B = 20;
    // 对常量取地址时，编译器会临时开辟一块内存空间，指针指向的是这块临时内存空间
    int *p = (int *) &m_B;
    *p = 30;
    cout << "*p = " << *p << endl;
    cout << "m_B = " << m_B << endl;
}

// 第二种情况
void test02() {
    int a = 40;
    // 使用普通变量初始化局部的常量，编译器会分配内存空间，可以通过指针更改值
    const int m_C = a;
    int *q = (int *) &m_C;
    *q = 50;
    cout << "*q = " << *q << endl;
    cout << "m_C = " << m_C << endl;
}

struct Person {
    int age;
    string name;
};

// 第三种情况
void test03() {
    // 使用 const 修饰自定义数据类型，编译器会分配内存，可以通过指针更改值
    const Person person = {18, "Jim"};
    Person *p = (Person *) &person;
    p->age = 20;
    p->name = "Tom";
    cout << "age = " << p->age << ", name = " << p->name << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}