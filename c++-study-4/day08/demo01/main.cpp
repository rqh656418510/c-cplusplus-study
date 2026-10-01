/**
 * 函数调用运算符、function类模板
 *
 * (a) 函数对象
 */

#include <iostream>

// 函数对象（仿函数）
class BiggerThanZero {
public:
    // 函数运算符重载
    bool operator()(const int val) const {
        return val > 0;
    }
};

int main() {
    const BiggerThanZero btz;
    const int result = btz(3);
    std::cout << result << std::endl;
    return 0;
}