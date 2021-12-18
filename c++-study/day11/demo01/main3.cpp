/*
 * 1. 容器初识（存放自定义数据类型）
*/

#include <iostream>
#include <vector>

using namespace std;

class Person {

public:
    Person(int age, string name) {
        this->age = age;
        this->name = name;
    }

    int getAge() {
        return this->age;
    }

    string getName() {
        return this->name;
    }

private:
    int age;
    string name;

};

int main() {
    Person p1(23, "Jim");
    Person p2(26, "Tom");
    Person p3(29, "Peter");

    // 定义容器
    vector<Person> v;

    // 插入数据
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    // 遍历容器
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "age = " << it->getAge() << ", name = " << it->getName() << endl;
        // 或者
        // cout << "age = " << (*it).getAge() << ", name = " << (*it).getName() << endl;
    }
    return 0;
}