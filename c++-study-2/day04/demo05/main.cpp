/**
 * 成员变量和成员属性分开处理
 */

#include <iostream>

using namespace std;

class Person {

};

class Student {

public:
    int m_A;                // 非静态成员变量，存储在对象内部
    static int m_B;         // 静态成员变量，不存储在对象内部
    void func() {};         // 非静态成员函数，不存储在对象内部
    static void func2() {}; // 静态成员函数，不存储在对象内部

};

void test01() {
    // 空类的大小为 1，每个实例对象都有一个独一无二的地址，char 负责维护这个地址
    cout << "size of (Person) " << sizeof(Person) << endl;
}

void test02() {
    cout << "size of (Student) " << sizeof(Student) << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
