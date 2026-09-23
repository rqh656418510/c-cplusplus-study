/**
 * 算法概述、内部处理、使用范例
 *
 * (c) find_if 算法的使用
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 56};

    // 查找第一个大于 15 的元素，第三个参数是可调用对象（如普通函数、函数对象、Lambda 表达式）
    std::vector<int>::iterator find_iter = std::find_if(numbers.begin(), numbers.end(), [](const int& number) { return number > 15; });

    if (find_iter != numbers.end()) {
        std::cout << "found number > 15, it is " << *find_iter << std::endl;
    } else {
        std::cout << "not found number > 15" << std::endl;
    }

    return 0;
}