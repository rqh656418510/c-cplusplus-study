/**
 * 可调用对象、std::function、std::bind
 *
 * (b) 类成员函数指针的使用
 */

#include <iostream>

class MyClass {
public:
    // 构造函数
    MyClass(const int i) : m_i(i) {
    }

    // 普通成员函数
    void process(int num) {
        std::cout << "m_i = " << m_i << std::endl;
        std::cout << "num = " << num << std::endl;
    }

private:
    int m_i = 0;  // 私有成员变量，默认初始化为 0
};

int main() {
    MyClass mc(5);  // 创建 MyClass 对象

    // 定义指向 MyClass 成员函数的指针
    // 类型为 void (MyClass::*)(int)，即 "指向 MyClass 中参数为 int、返回值为 void 的成员函数" 的指针
    // 这里让它指向 &MyClass::process
    void (MyClass::*fpointer)(int) = &MyClass::process;

    // 通过对象 mc 和成员函数指针 fpointer 调用成员函数
    // (mc.*fpointer) 表示通过对象 mc 解引用成员函数指针，后面的 (5) 是传给 process() 的参数
    (mc.*fpointer)(10);

    return 0;
}