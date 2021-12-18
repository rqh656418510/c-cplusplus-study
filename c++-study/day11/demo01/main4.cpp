/*
 * 1. 容器初识（存放自定义数据类型的指针）
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
    // 定义容器
    vector<Person *> v;

    // 插入数据
    v.push_back(new Person(23, "Jim"));
    v.push_back(new Person(26, "Tom"));
    v.push_back(new Person(29, "Peter"));

    // 遍历容器
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "age = " << (*it)->getAge() << ", name = " << (*it)->getName() << endl;
        // 或者
        // cout << "age = " << (**it).getAge() << ", name = " << (**it).getName() << endl;
    }
    return 0;
}