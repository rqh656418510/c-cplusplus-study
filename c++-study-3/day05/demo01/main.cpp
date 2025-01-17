/**
 * 继承的基本意义
 */

#include <iostream>

using namespace std;

// 定义基类（父类）
class Parent {

public:
    Parent(int a = 0, int b = 0) {
        this->a = a;
        this->b = b;
    }

    void print() {
        cout << "a=" << this->a << ", b=" << this->b << endl;
    }

public:
    int a;
    int b;
};

// 定义派生类（子类），继承方式是 public
class Child : public Parent {

public:

    Child(int a = 0, int b = 0, int c = 0) {
        // 直接访问基类（父类）的 public 成员变量
        this->a = a;
        this->b = b;
        this->c = c;
    }

    void echo() {
        cout << "a=" << this->a << ", b=" << this->b << ", c=" << this->c << endl;
    }

private:
    int c;
};

int main() {
    Child child(1, 2, 3);
    child.print();    // 直接调用基类（父类）的 public 成员函数
    child.echo();     // 直接调用派生类（子类）的 public 成员函数
    return 0;
}
