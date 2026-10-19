/**
 * 可调用对象、std::function、std::bind
 *
 * (e) std::bind 使用
 */

#include <functional>
#include <iostream>

class Calculator {
public:
    // 构造函数
    Calculator(const int i) : base(i) {
    }

    // 成员函数，隐含 this 参数
    int add(const int x) const {
        return base + x;
    }

private:
    // 成员变量，作为加法的基数
    int base;
};

void process(int x, int y, int z) {
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

int main() {
    auto bf = std::bind(process, 10, 20, 30);
    bf();

    auto bf2 = std::bind(process, std::placeholders::_1, std::placeholders::_2, 30);
    bf2(5, 3);

    std::bind(process, std::placeholders::_1, 10, 30)(5);

    Calculator ca(3);
    auto bf3 = std::bind(&Calculator::add, ca, std::placeholders::_1);
    std::cout << bf3(5) << std::endl;

    std::function<void(int, int)> bf4 = std::bind(process, std::placeholders::_1, std::placeholders::_2, 3);
    bf4(10, 8);

    return 0;
}