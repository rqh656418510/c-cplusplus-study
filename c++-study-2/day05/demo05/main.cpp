/**
 * 指针运算符重载，实现智能指针
 */
#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        this->m_Age = 0;
    }

    Person(int age) {
        this->m_Age = age;
    }

    ~Person() {
        cout << "调用Person的析构函数" << endl;
    }

    void showAge() {
        cout << "年龄 = " << this->m_Age << endl;
    }

private:
    int m_Age;

};

// 智能指针
class SmartPointer {

public:
    SmartPointer(Person *p) {
        this->person = p;
    }

    ~SmartPointer() {
        cout << "调用智能指针的析构函数" << endl;
        if (nullptr != this->person) {
            // 释放已托管的指针，会自动调用对应的析构函数
            delete (this->person);
            this->person = nullptr;
        }
    }

    // 重载 -> 符号
    Person *operator->() {
        return this->person;
    }

    // 重载 * 符号
    Person &operator*() {
        return *(this->person);
    }

private:
    Person *person;

};

void test01() {
    // 创建一个Person指针，并托管给智能指针对象，且在栈上给智能指针对象动态分配内存空间
    // 函数作用域结束后，会自动释放智能指针对象在栈上的内存空间，并自动调用智能指针对象的析构函数
    SmartPointer sp(new Person(20));

    // 原本的写法是 sp->->showAge()，只不过编译器做了优化
    sp->showAge();

    (*sp).showAge();
}

int main() {
    test01();
    return 0;
}
