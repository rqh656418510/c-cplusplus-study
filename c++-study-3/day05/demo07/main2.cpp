/**
 * 理解多态到底是什么
 */

#include <iostream>
#include <cstring>

using namespace std;

class Animal {

public:
    Animal(string name) : _name(name) {

    }

    // 虚函数
    virtual void bark() {

    }

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

void bark(Animal *animal) {
    // 动态多态（底层是通过动态绑定来实现的）
    animal->bark();
}

int main() {
    Cat cat = Cat("Cat");
    Dog dog = Dog("Dog");
    Pig pig = Pig("Pig");

    bark(&cat);
    bark(&dog);
    bark(&pig);

    return 0;
}
