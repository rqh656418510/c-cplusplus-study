/**
 * 基类与派生类关系的详细再探讨
 */

#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

// 基类
class Human {
public:
    Human(const string& name, int age) : m_Name(name), m_Age(age) {
        cout << "Human::Human(string, int)" << endl;
    }

    // 虚析构函数
    virtual ~Human() {
        cout << "Human::~Human()" << endl;
    }

    // 虚函数
    virtual void sleep() {
        cout << "Human::sleep()" << endl;
    }

protected:
    int m_Age;
    string m_Name;
};

// 派生类
class Men : public Human {
public:
    // 显式调用父类的有参构造函数
    Men() : Human("", 0) {
        cout << "Men::Men()" << endl;
    }

    // 显式调用父类的有参构造函数
    Men(const string& name, int age) : Human(name, age) {
        this->m_Name = name;
        this->m_Age = age;
        cout << "Men::Men(string, int)" << endl;
    }

    ~Men() {
        cout << "Men::~Men()" << endl;
    }

    virtual void sleep() override {
        cout << "Men::sleep()" << endl;
    }
};

// 定义不想被继承的基类
class Car final {};

int main() {
    // 父类的指针指向子类的对象
    Human* human = new Men("Jim", 18);

    // 多态调用，最终调用子类的成员函数 Men::sleep()
    human->sleep();

    delete human;

    return 0;
}