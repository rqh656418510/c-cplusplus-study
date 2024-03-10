/**
 * 构造函数的调用规则
 *
 * 当类中没有定义任何一个构造函数时，C++ 编译器会提供默认无参构造函数和默认拷贝构造函数
 * 当类中定义了拷贝构造函数时，C++ 编译器不会提供默认无参构造函数
 * 当类中定义了任意的非拷贝构造函数（即当类中定义了有参构造函数或无参构造函数），C++ 编译器不会提供默认无参构造函数
 */

#include <iostream>

using namespace std;

class Person {

public:

    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
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

int main() {
    // 当类中定义了任意的非拷贝构造函数（即当类中定义了有参构造函数或无参构造函数），C++ 编译器不会提供默认无参构造函数
    // Person p1;

    // 当类中没有定义拷贝构造函数时，编译器默认会提供一个拷贝构造函数，用于简单地进行类成员变量的值复制
    Person p2("Jim", 12);
    Person p3(p2);
    cout << "name = " << p3.getName() << ", age = " << p3.getAge() << endl;

    return 0;
}
