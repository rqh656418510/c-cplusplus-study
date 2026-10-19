/**
 * 可调用对象、std::function、std::bind
 *
 * (c) std::function 使用
 */

#include <functional>
#include <iostream>

// 普通类
class MyClass {
public:
    // 静态成员函数
    static void print(int val) {
        std::cout << "void MyClass::print(int val)" << std::endl;
    }
};

// 函数对象
class Student {
public:
    void operator()(int val) {
        std::cout << "void Student::operator()(int val)" << std::endl;
    }
};

// 普通函数
void process(int val) {
    std::cout << "void process(int)" << std::endl;
}

int main() {
    // std::function 绑定普通函数
    std::function<void(int)> fun1 = process;
    fun1(3);

    // std::function 绑定静态成员函数
    std::function<void(int)> fun2 = MyClass::print;
    fun2(5);

    // std::function 绑定函数对象
    Student student;
    std::function<void(int)> fun3 = student;
    fun3(5);

    return 0;
}