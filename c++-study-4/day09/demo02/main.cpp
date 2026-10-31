/**
 * 对象结构的发展和演化
 * 
 * (a) 带虚函数的对象
 */

#include <iostream>

// 带虚函数的类
class A {
public:
    // 虚函数，增加虚函数表指针
    virtual void func() {
    }

};

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 8

    std::cout << "sizeof(char *) = " << sizeof(char*) << std::endl;  // 输出 sizeof(char *) = 8
    std::cout << "sizeof(int *) = " << sizeof(int*) << std::endl;    // 输出 sizeof(int *) = 8
    std::cout << "sizeof(double *) = " << sizeof(double*) << std::endl;  // 输出 sizeof(double *) = 8
    return 0;
}