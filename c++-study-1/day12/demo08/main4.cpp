/*
 * 1. set / multiset 插入自定义数据类型
*/

#include <iostream>
#include <set>
#include <string>

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

private:
    string name;
    int age;

};

// 仿函数
class myCompare {
public:
    // 重载
    bool operator()(const Person &p1, const Person &p2) {
        // 排序规则
        return p1.getAge() > p2.getAge();
    }
};

void printCustomSet(set<Person, myCompare> &p) {
    // 遍历容器
    for (set<Person, myCompare>::iterator it = p.begin(); it != p.end(); it++) {
        cout << "name: " << it->getName() << ", age: " << it->getAge() << endl;
    }
}

int main() {

    set<Person, myCompare> s1;

    Person p1("Tom", 18);
    Person p2("Peter", 20);
    Person p3("Jim", 15);
    Person p4("David", 28);

    s1.insert(p1);
    s1.insert(p2);
    s1.insert(p3);
    s1.insert(p4);

    printCustomSet(s1);

    return 0;
}