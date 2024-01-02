/*
 * 1. 常用的查找算法 - find
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

void test01() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 查找基础数据类型
    vector<int>::iterator pos = find(v.begin(), v.end(), 5);
    if (pos != v.end()) {
        cout << "found value for " << *pos << endl;
    } else {
        cout << "not found value" << endl;
    }
}

void test02() {
    vector<Person> v;

    Person p1("Jim", 15);
    Person p2("Peter", 18);
    Person p3("David", 16);
    Person p4("Tom", 20);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    // 查找自定义数据类型
    // 自定义数据类型必须重载 == 操作符
    vector<Person>::iterator pos = find(v.begin(), v.end(), p2);
    if (pos != v.end()) {
        cout << "found person for " << pos->getName() << ", age is " << pos->getAge() << endl;
    } else {
        cout << "not found person" << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}
