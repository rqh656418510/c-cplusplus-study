/**
 * 基类指针、虚函数、纯虚函数、多态性、虚析构
 */

#include <iostream>

using namespace std;

// 基类（抽象类）
class Human {
public:
    Human() {
        cout << "Human::Human()" << endl;
    }

    Human(int age) {
        this->m_Age = age;
        cout << "Human::Human(int)" << endl;
    }

    // 虚析构函数
    virtual ~Human() {
        cout << "Human::~Human()" << endl;
    }

    // 纯虚函数
    virtual void sleep() = 0;

public:
    int m_Age;
    char m_Name[100];
};

// 派生类
class Men : public Human {
public:
public:
    Men() {
        cout << "Men::Men()" << endl;
    }

    ~Men() {
        cout << "Men::~Men()" << endl;
    }

    virtual void sleep() override {
        cout << "Men sleep" << endl;
    }
};

// 派生类
class Women : public Human {
public:
public:
    Women() {
        cout << "Women::Women()" << endl;
    }

    ~Women() {
        cout << "Women::~Women()" << endl;
    }

    virtual void sleep() override {
        cout << "Women sleep" << endl;
    }
};

int main() {
    // 拥有纯虚函数的类（抽象类）不能实例化
    // Human* human1 = new Human();

    // 父类的指针指向子类的对象
    Human* human2 = new Men();
    human2->sleep();  // 会发生多态，调用子类的成员函数 Men::sleep()
    delete human2;

    // 父类的指针指向子类的对象
    Human* human3 = new Women();
    human3->sleep();  // 会发生多态，调用子类的成员函数 Women::sleep()
    delete human3;

    return 0;
}