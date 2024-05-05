/**
 * 多态原理解析
 */

#include <iostream>

using namespace std;

class Animal {

public :
    virtual void speak() {
        cout << "Animal is speaking" << endl;
    }

};

class Cat : public Animal {

public:
    // 重写父类的虚函数
    virtual void speak() override {
        cout << "Cat is speaking" << endl;
    }

};

void doSpeak(Animal &animal) {
    animal.speak();
}

void test01() {
    cout << sizeof(Animal) << endl;
    cout << sizeof(Cat) << endl;
}

void test02() {
    // 父类的指针指向子类的对象，会发生多态
    Animal *animal = new Cat();
    animal->speak();

    // 虚函数的底层实现原理，下面的 *(int *) *(int *) animal 是函数地址
    ((void (*)()) (*(int *) *(int *) animal))();   // 效果相当于 animal->speak();
}

int main() {
    test01();
    test02();
    return 0;
}
