/**
 * 基类指针、虚函数、纯虚函数、多态性、虚析构
 */

#include <iostream>

using namespace std;

// 基类
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

    // 普通函数
    void eat() {
        cout << "Human eat food" << endl;
    }

    // 虚函数（用于多态）
    virtual void play() {
        cout << "Human play game" << endl;
    }

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

    void eat() {
        cout << "Men eat food" << endl;
    }

    virtual void play() override {
        cout << "Men play game" << endl;
    }
};

int main() {
    Human* human1 = new Human();
    human1->play();  // 调用父类的成员函数 Human::play()
    delete human1;

    cout << "====================" << endl;

    // 父类的指针指向子类的对象
    Human* human2 = new Men();

    human2->eat();          // 不会发生多态，调用父类的成员函数 Human::eat()
    human2->play();         // 会发生多态，调用子类的成员函数 Men::play()
    human2->Human::play();  // 通过作用域调用父类的成员函数 Human::play()

    delete human2;

    return 0;
}