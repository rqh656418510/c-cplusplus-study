/**
 * RTTI、dynamic_cast、typeid、虚函数表
 */

#include <iostream>

using namespace std;

// 基类
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

    // 多态调用，最终调用子类的成员函数 Men::sleep()
    human->sleep();

    // 安全的向下类型转换（父类 --> 子类）
    Men* men = dynamic_cast<Men*>(human);

    // 判断类型转换是否成功
    if (men != nullptr) {
        // 向下类型转换后，最终调用子类的成员函数 Men::eat()
        men->eat();
    }

    // 获取运行时的具体类型
    cout << typeid(*human).name() << endl;

    // 判断运行时的具体类型（不能使用 name() 来比较类型是否相同）
    if (typeid(*human) == typeid(Men)) {
        cout << "*human 指针指向 Men" << endl;
    }

    delete human;

    return 0;
}