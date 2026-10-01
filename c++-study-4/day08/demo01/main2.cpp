/**
 * 函数调用运算符、function类模板
 *
 * (b) function类模板
 */

#include <iostream>
#include <functional>

int echoValue(const int val) {
    std::cout << val << std::endl;
    return val;
}

int main() {
    std::function<int(int)> echo = echoValue;
    echo(10);
    return 0;
}