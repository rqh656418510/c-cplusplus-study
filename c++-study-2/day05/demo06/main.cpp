/**
 * 赋值运算符重载
 */
#include <iostream>
#include <cstring>

using namespace std;

class Person {

public:
    Person(int a) : m_A(a) {

    }

    int getA() const {
        return this->m_A;
    }

private:
    int m_A;
};

void test01() {
    Person p1(10);
    Person p2(0);
    // C++ 除了会默认提供无参构造函数、拷贝构造函数、析构函数，还会重载 `=` 赋值运算符
    // C++ 默认提供的 `=` 赋值运算符重载，属于浅拷贝，底层只会对类成员变量进行简单的拷贝（赋值）
    p2 = p1;
    cout << p2.getA() << endl;

}

class Person2 {

public:
    Person2(char *name) {
        this->pName = new char[strlen(name) + 1];
        strcpy(this->pName, name);
    }

    ~Person2() {
        if (nullptr != this->pName) {
            delete[] this->pName;
            this->pName = nullptr;
        }
    }

    Person2 &operator=(const Person2 &p) {
        // 释放内存空间
        if (nullptr != this->pName) {
            delete[] this->pName;
            this->pName = nullptr;
        }
        // 重新分配内存空间
        this->pName = new char[strlen(p.pName) + 1];
        strcpy(this->pName, p.pName);
        // 返回引用
        return *this;
    }

    char *getName() const {
        return this->pName;
    }

private :
    char *pName;

};

void test02() {
    Person2 p1("Peter");
    Person2 p2("Tom");
    Person2 p3("David");
    // 如果不自己重载 `=` 赋值运算符，对象的析构函数在执行时会出现深拷贝和浅拷贝问题，即同一块内存空间会被释放两次，从而导致程序异常退出
    p3 = p2 = p1;
    cout << p2.getName() << endl;
    cout << p3.getName() << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
