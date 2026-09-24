/**
 * 函数对象回顾、系统函数对象及范例
 *
 * (b) 标准库中的函数对象
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 56};

    // 使用 C++ 标准库中的函数对象进行降序排序（从大到小）
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    for_each(numbers.begin(), numbers.end(), [](const int& number) { std::cout << number << " "; });

    return 0;
}