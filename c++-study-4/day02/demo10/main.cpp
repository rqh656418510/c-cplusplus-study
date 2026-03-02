/**
 * RTTI、dynamic_cast、typeid、虚函数表
 */

#include <iostream>

using namespace std;

class Human {
public:
    Human() {
        cout << "Human::Human()" << endl;
    }

    Human(const string& name, int age) : m_Name(name), m_Age(age) {
        cout << "Human::Human(string, int)" << endl;
    }

    virtual ~Human() {
        cout << "Human::~Human()" << endl;
    }

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
    Men() {
        cout << "Men::Men()" << endl;
    }

    Men(const string& name, int age) {
        this->m_Age = age;
        this->m_Name = name;
        cout << "Men::Men(string, int)" << endl;
    }

    ~Men() {
        cout << "Men::~Men()" << endl;
    }

    virtual void sleep() override {
        cout << "Men::sleep()" << endl;
    }

    void eat() {
        cout << "Men::eat()" << endl;
    }
};

int main() {
    // 父类的指针指向子类的对象
    Human* human = new Men("Jim", 18);
    human->sleep();

    // 安全的向下类型转换
    Men* men = dynamic_cast<Men*>(human);
    men->eat();

    delete human;

    return 0;
}