/**
 * 继承中的构造和析构顺序
 *
 * <p> 子类可以继承父类的成员属性和成员函数，但是子类不会继承父类的构造函数和析构函数
 * <p> 因为只有父类自己知道如何构造和析构自己的成员属性，子类是不知道这一点的
 */

#include <iostream>

using namespace std;

class Base {

public:
    Base() {
        cout << "调用　Base 的构造函数" << endl;
    }

    ~Base() {
        cout << "调用　Base 的析构函数" << endl;
    }

};

class Son : public Base {

public:
    Son() {
        cout << "调用　Son 的构造函数" << endl;
    }

    ~Son() {
        cout << "调用　Son 的析构函数" << endl;
    }
};

void test01() {
    Son son;
}

int main() {
    test01();
    return 0;
}
