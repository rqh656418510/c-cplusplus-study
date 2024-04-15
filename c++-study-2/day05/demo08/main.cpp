/**
 * 关系运算符重载
 */
#include <iostream>

using namespace std;

class Person {

public:
    Person(string name, int age) : m_name(name), m_Age(age) {

    }

    bool operator==(Person p) {
        return this->m_name == p.m_name && this->m_Age == p.m_Age;
    }

    bool operator>(Person p) {
        return this->m_Age > p.m_Age;
    }

    bool operator<(Person p) {
        return this->m_Age < p.m_Age;
    }

private :
    string m_name;
    int m_Age;

};

void test01() {
    Person p1("Tom", 18);
    Person p2("Peter", 20);
    Person p3("Peter", 20);

    cout << (p1 < p2) << endl;
    cout << (p1 > p2) << endl;
    cout << (p2 == p3) << endl;
}

int main() {
    test01();
    return 0;
}
