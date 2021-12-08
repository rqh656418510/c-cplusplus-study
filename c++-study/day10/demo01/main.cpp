/*
 * 1. 类型转换
*/

#include <iostream>

using namespace std;

class Tree {

};

class Animal {

public:
    virtual void cry() = 0;

};

class Dog : public Animal {

public:
    void cry() override {
        cout << "dog cry ..." << endl;
    }

    void watchHome() {
        cout << "dog watch home" << endl;
    }

};

class Cat : public Animal {

public:
    void cry() override {
        cout << "cat cry ..." << endl;
    }

    void playBall() {
        cout << "cat play ball ..." << endl;
    }

};

void playAnimal(Animal* animal) {
    animal->cry();
    // 动态类型转换，将父类转换为子类，运行时会做类型检查
    Dog* dog = dynamic_cast<Dog*>(animal);
    if (dog != NULL) {
        dog->watchHome();
    }
    Cat* cat = dynamic_cast<Cat*>(animal);
    if (cat != NULL) {
        cat->playBall();
    }
}

void printBuf(const char* buf) {
    // const_cast 去除变量的 const 只读属性
    char* m_buf = const_cast<char*>(buf);
    m_buf[0] = 'b';
    cout << buf << endl;
    cout << m_buf << endl;
}

void printBuf2() {
    // 定义指针指向一个常量，这里的常量的内存空间不可以更改
    char* buf = "aaaaa";
    // const_cast 去除变量的 const 只读属性
    char* m_buf = const_cast<char*>(buf);
    // 此时若更改指针所指向的内存空间，会带来灾难性的后果
    m_buf[0] = 'b';
    cout << buf << endl;
    cout << m_buf << endl;
}

int main() {
    char* p1 = "hello";
    double pi = 3.1415926;

    // 静态类型转换，编译的时候 C++ 编译器会做类型检查
    int num1 = static_cast<int>(pi);
    cout << "num1 = " << num1 << endl;

    // 静态类型转换，基本类型都能转换，但是不能转换指针类型（多态除外）
    // int* p2 = static_cast<int*>(p1);  // 错误写法，C++ 编译器编译失败

    // 重新解释类型，不同类型之间会进行强制类型转换，包括转换指针类型
    int* p2 = reinterpret_cast<int*>(p1);
    cout << "p2 = " << p2 << endl;

    // 去除变量的 const 只读属性
    char buf[] = "aaaaa";
    printBuf(buf);
    // printBuf2();

    // 动态类型转换，基类和派生类之间转换，运行时会做类型检查
    Dog dog;
    Cat cat;
    playAnimal(&dog);
    playAnimal(&cat);

    // 多态的其他使用场景
    Animal* pAnimal = NULL;
    pAnimal = &dog;
    pAnimal = static_cast<Animal*>(&dog); // 编译通过
    pAnimal->cry();
    pAnimal = reinterpret_cast<Animal*>(&dog); // 编译通过
    pAnimal->cry();

    Tree tree;
    // pAnimal = static_cast<Animal*>(&tree); // 错误写法，C++ 编译器编译失败
    pAnimal = reinterpret_cast<Animal*>(&tree); // 编译通过

    return 0;
}