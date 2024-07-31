/**
 * 友元碰到类模板-友元函数类外实现
 */

#include <iostream>

using namespace std;

/********** START 解决类模板与友元函数的编译问题 *********/

// 让编译器提前看到 Person 类的声明
template<class T1, class T2> class Person;

// 让编译器提前看到 printPerson 函数的声明
template<class T1, class T2> void printPerson(Person<T1, T2> &p);

/********** END 解决类模板与友元函数的编译问题 *********/

template<class T1, class T2>
class Person {

public:

    Person(T1 name, T2 age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    // 定义友元函数，并使用空参数列表来让编译器强制调用函数模板
    friend void printPerson<>(Person<T1, T2> &p);

private:
    T1 m_Name;
    T2 m_Age;

};

// 在类外实现友元函数（相当于全局函数）
template<class T1, class T2>
void printPerson(Person<T1, T2> &p) {
    cout << "name: " + p.m_Name + ", age: " << p.m_Age << endl;
}

int main() {
    Person<string, int> p("Tom", 20);
    printPerson(p);
    return 0;
}
