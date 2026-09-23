/**
 * 算法概述、内部处理、使用范例
 *
 * (a) 算法的使用
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 5};
    std::vector<int>::iterator iter_begin = numbers.begin();
    std::vector<int>::iterator iter_end = numbers.end();

    std::sort(iter_begin, iter_end);

    for (const auto &num : numbers) {
        std::cout << num << std::endl;
    }

    return 0;
}