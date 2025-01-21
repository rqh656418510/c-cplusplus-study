/**
 * 继承多态笔试题实战分析
 *
 * <p> 高频面试题一
 */

#include <iostream>

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

int main() {
    Animal *p1 = new Cat("Cat");
    Animal *p2 = new Dog("Dog");

    int *p11 = (int *) p1;  // p11[0] 指向的是 Cat 的前 4 个字节（存放的是 vfptr）
    int *p22 = (int *) p2;  // p22[0] 指向的是 Dog 的前 4 个字节（存放的是 vfptr）

    int tmp = p11[0];   // 交换两个对象的虚函数指针（vfptr）的地址
    p11[0] = p22[0];
    p22[0] = tmp;

    p1->bark();     // p1 -> Cat vfptr -> Dog vftable，输出：Cat bark: wang wang
    p2->bark();     // p2 -> Dog vfptr -> Cat vftable，输出：Dog bark: miao miao

    delete p1;
    delete p2;

    return 0;
}