/**
 * 1. C++ 对 C 语言的增强
 */

#include <iostream>

using namespace std;

struct Student {
    int age;
    char name[100];

    // C++ 中结构体内可以定义函数，而 C 语言则不允许
    void plusAge() {
        age++;
    };
};

int main(int argc, char *argv[]) {

    /************************ struct 类型的增强 ******************************/

    Student s1 = {18, "wang"};                  // C 语言编译器编译报错，C++ 编译器编译通过
    struct Student s2 = {20, "chen"};           // C 语言编译器编译通过
    return 0;
}