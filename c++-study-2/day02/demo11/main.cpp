/**
 * 构造函数的分类及调用
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        cout << "无参构造函数" << endl;
    }

    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    Person(const Person &p) {
        this->name = p.name;
        this->age = p.age;
        cout << "拷贝构造函数" << endl;
    }

private:
    string name;
    int age;

};

int main() {
    // 自动调用无参构造函数
    Person p1;

    // 自动调用有参构造函数
    Person p2("Jim", 23);

    // 自动调用拷贝构造函数
    Person p3 = p2;

    return 0;
}
