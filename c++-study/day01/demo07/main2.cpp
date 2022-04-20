/**
 * 1. C++中的引用之引用作函数参数
 */

#include <iostream>

using namespace std;

struct Teacher {
    char name[64];
    int age;
};

// pT是指向t1的指针，这里相当于修改了t1
void printfT(Teacher *pT) {
    cout << pT->age << endl;
    pT->age = 23;
}

// pT是t1的别名，这里相当于修改了t1
void printfT2(Teacher & pT) {
    cout << pT.age << endl;
    pT.age = 33;
}

// pT和t1的是两个不同的变量，这里只会修改pT变量，不会修改t1变量
void printfT3(Teacher pT) {
    cout << pT.age << endl;
    pT.age = 43;
}

int main() {
    Teacher t1;
    t1.age = 35;

    // pT是指向t1的指针
    printfT(&t1);
    printf("t1.age:%d \n", t1.age);

    // pT是t1的别名
    printfT2(t1);
    printf("t1.age:%d \n", t1.age);

    // pT是形参，相当于t1复制一份数据给pT ---> pT = t1
    printfT3(t1);
    printf("t1.age:%d \n", t1.age);
    return 0;
}