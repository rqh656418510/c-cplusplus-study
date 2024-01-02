/*
 * 1. 常用的查找算法 - find_if
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

// 自定义数据类型
class Person {

public:

    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    string getName() const {
        return this->name;
    }

    int getAge() const {
        return this->age;
    }

    // 重载 == 操作符
    bool operator==(const Person &p) {
        return this->name == p.name && this->age == p.age;
    }

private :

    string name;
    int age;

};

// 函数对象
class MyPersonCompare : public binary_function<Person *, Person *, bool> {

public:

    // 重载 () 操作符
    bool operator()(Person *p1, Person *p2) const {
        return p1->getName() == p2->getName() && p1->getAge() == p2->getAge();
    }

};

int main() {
    vector<Person *> v;

    Person p1("Jim", 15);
    Person p2("Peter", 18);
    Person p3("David", 16);
    Person p4("Tom", 20);

    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);

    Person *p5 = new Person("David", 16);

    // 根据条件查找
    vector<Person *>::iterator pos = find_if(v.begin(), v.end(), bind2nd(MyPersonCompare(), p5));
    if (pos != v.end()) {
        cout << "found person for " << (*pos)->getName() << ", age is " << (*pos)->getAge() << endl;
    } else {
        cout << "not found person" << endl;
    }

    return 0;
}
