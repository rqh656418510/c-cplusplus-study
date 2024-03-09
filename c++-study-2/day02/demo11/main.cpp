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

    cout << "-----------普通构造函数调用-----------" << endl;

    // 自动调用无参构造函数
    Person p1;

    // 以下是错误写法，无参构造函数的调用不要加括号，否则 C++ 编译器会认为是函数的声明，导致构造函数不会被调用
    // Person p1();

    // 自动调用有参构造函数(括号法)
    Person p2("Jim", 23);

    // 手动调用有参构造函数(显式法)
    Person p6 = Person("Tom", 18);

    cout << "-----------拷贝函数调用-----------" << endl;

    // 自动调用拷贝构造函数(等号法)
    Person p3 = p2;

    // 自动调用拷贝构造函数(括号法)
    Person p4(p2);

    // 自动调用拷贝构造函数
    Person p5 = Person(p2);

    return 0;
}
