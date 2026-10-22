/**
 * 可变参数函数、initializer_list、省略号形参
 *
 * (c) 省略号形参
 */

#include <cstdarg>
#include <iostream>

int sum(const int count, ...) {
    va_list args;
    va_start(args, count);  // 以最后一个具名形参为起点
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += va_arg(args, int);  // 每次按 int 类型读取一个实参
    }
    va_end(args);  // 清理
    return sum;
}

int main() {
    int result = sum(5, 10, 20, 30, 40, 50);
    std::cout << result << std::endl;
    return 0;
}