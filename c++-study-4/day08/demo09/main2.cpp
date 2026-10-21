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
        // 按值捕获成员变量，相当于捕获了 this 指针（[this]）
        vec.push_back([=](const int val) { return val % m_num == 0; });
    }

private:
    int m_num = 5;
};

int main() {
    MyClass* mc = new MyClass();
    mc->addItem();
    delete mc;

    int result = vec[0](10);  // 存在悬垂 this 指针导致的未定义行为
    std::cout << result << std::endl;

    return 0;
}