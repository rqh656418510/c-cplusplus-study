/**
 * 算法概述、内部处理、使用范例
 *
 * (a) for_each 算法的使用
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 56};

    // 第三个参数是可调用对象（如普通函数、函数对象、Lambda 表达式）
    std::for_each(numbers.begin(), numbers.end(), [](const int number) { std::cout << number << " "; });

    return 0;
}