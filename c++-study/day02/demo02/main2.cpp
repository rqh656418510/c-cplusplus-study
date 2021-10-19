/**
 * 1. C++中的引用之常引用（使用变量初始化 const 引用）
 */

#include <iostream>

using namespace std;

struct Teacher {
    char name[64];
    int age;
};

// const引用让变量(所指内存空间)拥有只读属性
void printTe(const Teacher &t) {
    // t.age = 11;   是错误写法，无法通过编译
}

// const 修饰指针和指针指向的内容，那么指针指向的内容都不能更改
void printTe2(const Teacher *const pt) {
    // pt->age = 11;  是错误写法，无法通过编译
}

int main() {
    Teacher t1;
    t1.age = 33;
    printTe(t1);
    printTe2(&t1);
    return 0;
}