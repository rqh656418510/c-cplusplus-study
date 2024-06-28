/**
 * 成员函数创建时机
 */

#include "iostream"

using namespace std;

class Person1 {

public:
    void showPerson1() {
        cout << "Person1" << endl;
    }

};

class Person2 {

public:
    void showPerson2() {
        cout << "Person2" << endl;
    }

};

template<class T>

class MyClass {

public:

    // 成员函数一开始不会创建出来，而是在运行时才会创建
    void func1() {
        obj.showPerson1();
    }

    // 成员函数一开始不会创建出来，而是在运行时才会创建
    void func2() {
        obj.showPerson2();
    }

    T obj;

};

int main() {
    MyClass<Person1> c1;
    c1.func1();

    MyClass<Person2> c2;
    c2.func2();

    return 0;
}
