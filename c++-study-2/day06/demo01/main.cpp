/**
 * 静态联编和动态联编
 */

#include <iostream>

using namespace std;

class Animal {

public :
    // 在父类中声明虚函数
    // 函数的调用地址不能在编译期间确定，而是需要在运行时才能决定，属于晚绑定，即运行时多态（动态多态、动态联编）
    virtual void speak() {
        cout << "Animal is speaking" << endl;
    }

};

class Cat : public Animal {

public:
    // 重写父类的虚函数
    // 只要父类中的函数有 "virtual" 关键字的声明，那么子类的 "virtual" 关键字声明可写可不写，一般建议都写上
    virtual void speak() override {
        cout << "Cat is speaking" << endl;
    }

};

void doSpeak(Animal &animal) {
    animal.speak();
}

void test01() {
    Cat cat;

    // 执行子类的函数，默认情况下子类中重写的函数将隐藏父类中的函数
    cat.speak();

    // 执行父类的函数，通过作用域分辨符"::"可以访问到父类中被隐藏的函数
    cat.Animal::speak();
}

void test02() {
    Animal animal;
    doSpeak(animal);

    Cat cat;
    doSpeak(cat);
}

int main() {
    test01();
    cout << "--------------------" << endl;
    test02();
    return 0;
}
