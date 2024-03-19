/**
 * new 运算符的使用
 */

#include <iostream>

using namespace std;

class Person {

public:

    Person() {
        cout << "默认构造函数调用" << endl;
    }

    ~Person() {
        cout << "析构函数调用" << endl;
    }

};

void test01() {
    Person p1;  // 创建对象（静态），会在栈上开辟内存空间，对象所在的作用域结束后或者程序结束后都会自动释放内存空间，即会自动调用析构函数
    Person *p2 = new Person();  // 创建对象（动态），会在堆上开辟内存空间，对象所在的作用域结束后或者程序结束后都不会自动释放内存空间，即不会自动调用析构函数
    delete p2;  // 释放对象所在的堆内存空间，会自动调用析构函数
}

void test02() {
    void *p = new Person();  // 当使用 void * 接收 new 出来的指针，会出现内存释放的问题
    delete p;   // 无法释放内存空间，并且不会自动调用析构函数
}

int main() {
    cout << "------- test01() -------" << endl;
    test01();
    cout << "------- test02() -------" << endl;
    test02();
    return 0;
}
