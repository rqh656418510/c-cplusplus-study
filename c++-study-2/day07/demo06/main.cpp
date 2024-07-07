/**
 * 类模板的基本使用
 */

#include <iostream>

using namespace std;

// 类模板声明（类模板支持默认类型）
template<class T1, class T2 = int>

class Person {

public:

    Person(T1 name, T2 age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    void show() {
        cout << "name = " + this->m_Name + ", age = " << this->m_Age;
    }

    T1 m_Name;
    T2 m_Age;

};

void test01() {
    Person<string, int> p1("Jim", 20);
    p1.show();

    // 类模板支持默认类型
    Person<string> p2("Tom", 20);
    p2.show();
}

int main() {
    test01();
    return 0;
}
