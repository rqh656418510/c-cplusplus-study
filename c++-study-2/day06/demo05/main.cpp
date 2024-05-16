/**
 * 虚析构函数
 *
 * <p> 虚析构函数使得在删除指向子类对象的父类指针时，可以调用子类的析构函数来实现释放子类中堆内存的目的，从而防止内存泄漏
 */

#include <iostream>
#include <cstring>

using namespace std;

class Animal {

public :
    virtual void speak() {
        cout << "Animal speaking ..." << endl;
    }

    // 定义虚析构函数
    virtual ~Animal() {
        cout << "调用 Animal 的析构函数" << endl;
    }

};

class Cat : public Animal {

public:
    Cat(char *name) {
        // 分配内存空间
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
    Animal *animal = new Cat("Tom");
    animal->speak();
    delete animal;
}

int main() {
    test01();
    return 0;
}
