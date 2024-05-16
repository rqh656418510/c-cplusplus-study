/**
 * 纯虚析构函数
 *
 * <p> 纯虚析构函数必须在类内声明，类外实现
 * <p> 如果类拥有纯析构函数，那么这个类也算是抽象类，即该类不能实例化对象
 */

#include <iostream>
#include <cstring>

using namespace std;

class Animal {

public :
    virtual void speak() {
        cout << "Animal speaking ..." << endl;
    }

    // 声明纯虚析构函数
    virtual ~Animal() = 0;

};

// 定义纯虚析构函数
Animal::~Animal() {
    cout << "调用 Animal 的析构函数" << endl;
}

class Cat : public Animal {

public:
    Cat(char *name) {
        // 分配内存空间（必须在类内声明，类外实现）
        this->m_Name = new char[strlen(name) + 1];
        strcpy(this->m_Name, name);
    }

    virtual void speak() {
        cout << "Cat speaking ..." << endl;
    }

    ~Cat() {
        cout << "调用 Cat 的析构函数" << endl;
        // 释放内存空间
        if (this->m_Name != nullptr) {
            delete[] this->m_Name;
            this->m_Name = nullptr;
        }
    }

public:
    char *m_Name;

};

void test01() {
    // 错误写法，不能实例化对象
    // 如果类拥有纯析构函数，那么这个类也算是抽象类，即该类不能实例化对象
    // Animal *animal = new Animal();

    Animal *animal = new Cat("Tom");
    animal->speak();
    delete animal;
}

int main() {
    test01();
    return 0;
}
