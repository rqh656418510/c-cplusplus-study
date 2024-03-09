/**
 * 构造函数和析构函数的使用
 */

#include <iostream>

using namespace std;

class Person {

public:

    // 无参构造函数
    Person() {
        cout << "无参构造函数" << endl;
    }

    // 有参构造函数
    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    // 析构函数
    ~Person() {
        this->name = "";
        this->age = 0;
        cout << "析构函数" << endl;
    }

private:
    string name;
    int age;

};

void test01() {
    // 自动调用无参构造函数
    Person p1;

    // 自动调用有参构造函数
    Person p2("Jim", 28);

    // 由于 p1 与 p2 变量的生命周期只在函数内部有效，因此在函数结束调用前，Person 对象的析构函数会被自动调用
}

int main() {
    test01();
    return 0;
}
