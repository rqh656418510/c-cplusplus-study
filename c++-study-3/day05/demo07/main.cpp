/**
 * 理解抽象类
 */

#include <iostream>
#include <cstring>

using namespace std;

// 抽象类
class Animal {

public:
    // 抽象类可以有构造函数，用于初始化其成员变量
    // 当抽象类被继承并通过派生类构造时，抽象类的构造函数会被调用
    Animal(string name) : _name(name) {
        cout << "Animal()" << endl;
    }

    // 抽象类可以有析构函数，用于释放资源
    // 当抽象类被继承并通过派生类析构时，抽象类的析构函数会被调用
    ~Animal() {
        cout << "~Animal()" << endl;
    }

    // 纯虚函数
    virtual void bark() = 0;

protected:
    string _name;

};

class Cat : public Animal {

public:
    Cat(string name) : Animal(name) {

    }

    void bark() {
        cout << _name << " bark: miao miao" << endl;
    }

};

class Dog : public Animal {

public:
    Dog(string name) : Animal(name) {

    }

    void bark() {
        cout << _name << " bark: wang wang" << endl;
    }

};

class Pig : public Animal {

public:
    Pig(string name) : Animal(name) {

    }

    void bark() {
        cout << _name << " bark: heng heng" << endl;
    }

};

void bark(Animal &animal) {
    // 动态多态（底层是通过动态绑定来实现的）
    animal.bark();
}

int main() {
    // 错误写法，抽象类不能实例化
    // Animal animal("Animal");

    Cat cat = Cat("Cat");
    Dog dog = Dog("Dog");
    Pig pig = Pig("Pig");

    bark(cat);
    bark(dog);
    bark(pig);

    return 0;
}
