/**
 * 1. C++ 中指针引用
 */

#include <iostream>

using namespace std;

struct Person {
    int age;
};

// 二级指针作函数参数
// 这里的函数参数中，**p 是 Person 对象，*p 是 Person 对象的指针，p 是指针的指针
void allocatMemory1(Person **p) {
    *p = (Person *) malloc(sizeof(Person));
    (*p)->age = 18;
}

void test01() {
    Person *p = NULL;
    allocatMemory1(&p);
    cout << "age = " << p->age << endl;
}

// 指针引用作函数参数
void allocatMemory2(Person *&p) {
    p = (Person *) malloc(sizeof(Person));
    p->age = 20;
}

void test02() {
    Person *p = NULL;
    allocatMemory2(p);
    cout << "age = " << p->age << endl;
}

int main() {
    test01();
    test02();
}
