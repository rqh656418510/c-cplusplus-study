/**
 * this 指针的使用
 */

#include <iostream>

using namespace std;

class Person {

public:

    Person() {

    }

    // 当形参和成员变量同名时，可用 this 指针来区分
    Person(int age) {
        this->age = age;
    }

    // 编译器会自动加上一个 this 指针参数：Person * const this
    void showAge() {
        cout << "age = " << this->age << endl;
    }

    // 在类的非静态成员函数中返回对象本身时，可以使用 return *this
    Person &addAge(const Person &p) {
        this->age += p.age;
        return *this;
    }

private:
    int age = 0;

};


int main() {
    Person p1(18);
    p1.showAge();

    Person p2(26);
    p2.showAge();

    Person p3(23);
    p1.addAge(p2).addAge(p3);
    p1.showAge();
    
    return 0;
}
