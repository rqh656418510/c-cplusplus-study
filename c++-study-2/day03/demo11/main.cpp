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

    Person(int age) : mAge(age) {
        cout << "有参构造函数调用" << endl;
    }

    ~Person() {
        cout << "析构函数调用" << endl;
    }

private:
    int mAge;

};

void test01() {
    Person p1;  // 创建对象（静态），会在栈上开辟内存空间，对象所在的作用域结束后或者程序结束后都会自动释放内存空间，会自动调用析构函数

    Person *p2 = new Person();  // 通过 new 运算符创建对象（动态），会在堆上开辟内存空间，对象所在的作用域结束后或者程序结束后都不会自动释放内存空间，不会自动调用析构函数
    delete p2;  // 通过 delete 运算符释放对象所在的堆内存空间，会自动调用析构函数
}

void test02() {
    void *p = new Person();  // 当使用 void * 类型接收 new 出来的指针时，会出现内存释放问题
    delete p;   // 无法正确释放内存空间，并且不会自动调用析构函数
}

void test03() {
    Person *pArray = new Person[3]; // 通过 new 运算符创建对象数组时（动态），一定会自动调用类的默认构造函数，所以必须提供类的默认构造函数，否则编译不通过
    delete[] pArray;   // 通过 delete 运算符释放对象数组的内存空间
}

void test04() {
    Person pArray2[2] = {Person(1), Person(2)};  // 创建对象数组（静态），会在栈上开辟内存空间，可以指定有参构造函数
}

int main() {
    cout << "------- test01() -------" << endl;
    test01();
    cout << "------- test02() -------" << endl;
    test02();
    cout << "------- test03() -------" << endl;
    test03();
    cout << "------- test04() -------" << endl;
    test04();
    return 0;
}
