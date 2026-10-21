/**
 * Lambda 表达式捕获模式的陷阱分析和展示
 *
 * (b) Lambda 表达式使用陷阱 - 成员变量捕获问题
 */

#include <functional>
#include <iostream>
#include <vector>

std::vector<std::function<bool(int)>> vec;

class MyClass {
public:
    void addItem() {
        // 错误写法：按值捕获成员变量，相当于捕获了 this 指针（[this]），存在悬垂 this 指针导致的未定义行为
        // vec.push_back([=](const int val) { return val % m_num == 0; });

        // 正确写法：拷贝成员变量到临时变量，Lambda 表达式按值捕获临时变量，然后在函数体内使用临时变量的副本
        int tmp = m_num;
        vec.push_back([tmp](const int val) { return val % tmp == 0; });
    }

private:
    int m_num = 5;
};

int main() {
    MyClass* mc = new MyClass();
    mc->addItem();
    delete mc;

    int result = vec[0](10);
    std::cout << result << std::endl;

    return 0;
}