/**
 * 算法概述、内部处理、使用范例
 *
 * (d) sort 算法的使用
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 56};

    // 排序（默认升序排序，即从小到大排序）
    std::sort(numbers.begin(), numbers.end());

    // 或者降序排序（即从大到小排序），第三个参数是可调用对象（如普通函数、函数对象、Lambda 表达式）
    // std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    for (const int& number : numbers) {
        std::cout << number << " ";
    }

    return 0;
}