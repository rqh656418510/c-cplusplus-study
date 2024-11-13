/**
 * const、指针、引用的结合使用
 */

#include <iostream>

using namespace std;

struct Person {
    int age;
};

// 二级指针作函数参数，参数 p 是一个指向 Person 指针的指针
void allocatMemory1(Person **p) {
    // 动态分配内存给 *p，使其指向一个新的 Person 对象
    *p = (Person *) malloc(sizeof(Person));
    (*p)->age = 18;
}

void test01() {
    // 定义一个 Person 类型的指针 p，初始化为 NULL（空指针）
    Person *p = NULL;
    // 传入 &p（Person* 的地址）
    allocatMemory1(&p);
    cout << "age = " << p->age << endl;
}

// 指针引用作函数参数，参数 p 是 Person* 类型的引用
void allocatMemory2(Person *&p) {
    // 动态分配内存给 p，使其指向一个新的 Person 对象
    p = (Person *) malloc(sizeof(Person));
    p->age = 20;
}

void test02() {
    // 定义一个 Person 类型的指针 p，初始化为 NULL（空指针）
    Person *p = NULL;
    // 直接传入 p
    allocatMemory2(p);
    cout << "age = " << p->age << endl;
}

int main() {
    // 常量引用
    const int &num = 30;

    // 在内存的0x0018ff44位置写一个4字节的10
    // int *p = (int *) 0x0018ff44;

    // 二级指针
    int a = 10;
    int *p = &a;
    int **q = &p;
    cout << **q << endl;

    // 二级指针
    test01();

    // 指针引用
    test02();

    return 0;
}
