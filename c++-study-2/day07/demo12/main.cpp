/**
 * 友元碰到类模板-友元函数类内实现
 */

#include <iostream>

using namespace std;

template<class T1, class T2>
class Person {

public:

    Person(T1 name, T2 age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    // 在类内实现友元函数（相当于全局函数）
    friend void printPerson(Person<T1, T2> &p) {
        cout << "name: " + p.m_Name + ", age: " << p.m_Age << endl;
    }

private:
    T1 m_Name;
    T2 m_Age;

};

void test01() {
    Person<string, int> p("Tom", 20);
    printPerson(p);
}

int main() {
    test01();
    return 0;
}
