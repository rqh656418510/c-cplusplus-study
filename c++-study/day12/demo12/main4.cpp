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

int main() {
    vector<Person> v;
    v.push_back(Person("Jim", 15));
    v.push_back(Person("Peter", 18));
    v.push_back(Person("David", 16));
    v.push_back(Person("Tom", 20));

    // 遍历打印数据
    // mem_fun_ref 可以将成员函数适配为函数对象
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showPerson));

    return 0;
}
