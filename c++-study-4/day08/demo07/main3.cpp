/**
 * 可调用对象、std::function、std::bind
 *
 * (c) std::function 使用
 */

#include <functional>
#include <iostream>

class MyClass {
public:
    // 静态成员函数
    static void print(int val) {
        std::cout << "void MyClass::print(int val)" << std::endl;
    }
};

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

    return 0;
}