/**
 * 派生类、调用顺序、访问等级、函数遮蔽
 */

#include <iostream>

using namespace std;

// 基类
class Human {
public:
    Human() {
        cout << "Human::Human()" << endl;
    }

    Human(int age) {
        this->m_Age = age;
        cout << "Human::Human(int)" << endl;
    }

    ~Human() {
        cout << "Human::~Human()" << endl;
    }

public:
    int m_Age;
    char m_Name[100];

    void funcPub() {
        cout << "Human::funcPub()" << endl;
    }

    void funcSameName() {
        cout << "Human::funcSameName()" << endl;
    }

    void funcSameName(int) {
        cout << "Human::funcSameName(int)" << endl;
    }

protected:
    char m_Phone[20];

    void funcPro() {
        cout << "Human::funcPro()" << endl;
    }

private:
    char m_Birthday[50];

    void funcPri() {
        cout << "Human::funcPri()" << endl;
    }
};

// 派生类
class Men : public Human {
public:
    using Human::funcSameName;

public:
    Men() {
        cout << "Men::Men()" << endl;
    }

    ~Men() {
        cout << "Men::~Men()" << endl;
    }

    void funcSameName(int) {
        Human::funcSameName();   // 调用父类的不带参的同名函数
        Human::funcSameName(5);  // 调用父类的带参的同名函数
        cout << "Men::funcSameName(int)" << endl;
    }
};

int main() {
    Men men;
    // men.funcPri();  // 无法调用父类成员函数
    // men.funcPro();  // 无法调用父类成员函数
    men.funcPub();  // 正常调用父类成员函数

    men.funcSameName(3);  // 正常调用子类同名成员函数

    // men.funcSameName();  // 默认情况下，无法调用父类同名成员函数（子类中如果有一个同名函数，那么父类中不管有多少个同名函数，子类中都无法访问到父类的同名函数）

    // 通过 using 关键字，让父类的同名函数在子类中可见，也就是让父类同名函数在子类中以重载的方式来使用
    men.funcSameName();

    return 0;
}