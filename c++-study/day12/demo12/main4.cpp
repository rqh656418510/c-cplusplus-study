/*
 * 1. 成员函数适配器的使用
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Person {

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    void showPerson() {
        cout << "name: " << this->name << ", age: " << this->age << endl;
    }

    string name;
    int age;

};

void test01() {

    cout << "----------- 成员函数适配器 mem_fun_ref 的使用 -------------" << endl;

    vector<Person> v;

    Person p1("Jim", 15);
    Person p2("Peter", 18);
    Person p3("David", 16);
    Person p4("Tom", 20);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    // 遍历打印数据
    // mem_fun_ref 可以将成员函数适配为函数对象
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showPerson));
}

void test02() {

    cout << "----------- 成员函数适配器 mem_fun 的使用 -------------" << endl;

    vector<Person *> v;

    Person p1("Jim", 15);
    Person p2("Peter", 18);
    Person p3("David", 16);
    Person p4("Tom", 20);

    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);


    // 遍历打印数据
    // mem_fun 可以将成员函数适配为函数对象
    for_each(v.begin(), v.end(), mem_fun(&Person::showPerson));
}

int main() {
    test01();
    test02();
    return 0;
}
