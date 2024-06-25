/**
 * 函数模板的局限性
 */

#include "iostream"

using namespace std;

class Person {

public:

    Person(string name, int age) {
        this->m_name = name;
        this->m_age = age;
    }

    string m_name;
    int m_age;

};

template<class T>
bool myCompare(T &a, T &b) {
    return a == b;
}

void test01() {
    int a = 10;
    int b = 20;
    bool resutlt = myCompare(a, b); // 传入基础数据类型
    cout << resutlt << endl;
}

// 通过第三代具体化自定义数据类型，解决函数模板的局限性问题
// 如果具体化能够优先匹配，那么就选择具体化
template<> bool myCompare<Person>(Person &a, Person &b) {
    return a.m_age == b.m_age;
}

void test02() {
    Person p1("Tom", 23);
    Person p2("Jim", 23);

    bool resutlt = myCompare(p1, p2);  // 传入自定义数据类型
    cout << resutlt << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
