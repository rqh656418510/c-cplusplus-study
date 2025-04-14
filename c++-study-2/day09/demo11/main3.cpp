/*
 * 1. map 使用自定义数据类型作为 Key
*/

#include <iostream>
#include <map>

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

void printMap(map<Person, string, myCompare> &m) {
    // 遍历容器
    for (map<Person, string, myCompare>::iterator it = m.begin(); it != m.end(); it++) {
        cout << "age = " << it->first.getAge() << ", name = " << it->first.getName() << ", role = " << it->second << endl;
    }
}

int main() {
    // 使用仿函数，让 map 容器按照年龄进行倒序排序（从大到小）
    map<Person, string, myCompare> m1;
    m1.insert(make_pair(Person("Tom", 19), "Student"));
    m1.insert(make_pair(Person("Jim", 18), "Student"));
    m1.insert(make_pair(Person("Peter", 28), "Teacher"));
    printMap(m1);
    return 0;
}
