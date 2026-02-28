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

    void eat() {
        cout << "Women eat food" << endl;
    }

    virtual void play() override {
        cout << "WoMen play game" << endl;
    }
};

int main() {
    // 父类的指针指向子类的对象
    Human* human = new Men();

    human->eat();   // 调用父类的成员函数
    human->play();  // 调用子类的成员函数（多态）

    delete human;

    return 0;
}