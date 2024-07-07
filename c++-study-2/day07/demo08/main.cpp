/**
 * 类模板做函数的参数
 */

#include <iostream>
#include <typeinfo>

using namespace std;

// 类模板声明
template<class T1, class T2>

class Person {

public:

    Person(T1 name, T2 age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    void show() {
        cout << "name = " + this->m_Name + ", age = " << this->m_Age << endl;
    }

    T1 m_Name;
    T2 m_Age;

};

// 第一种传参方式：指定传入类型
void doWork1(Person<string, int> &p) {
    p.show();
}

void test01() {
    Person<string, int> p("Jim", 18);
    doWork1(p);
}

// 第二种传参方式：参数模板化（函数模板 + 类模板）
template<class T1, class T2>
void doWork2(Person<T1, T2> &p) {
    p.show();
    // 在运行时查看对象的类型信息
    // cout << typeid(T1).name() << endl;
    // cout << typeid(T2).name() << endl;
}

void test02() {
    Person<string, int> p("Tom", 20);
    doWork2(p);
}

// 第三种传参方式：整体模板化（函数模板）
template<class T>
void doWork3(T &p) {
    p.show();
}

void test03() {
    Person<string, int> p("Peter", 22);
    doWork3(p);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
