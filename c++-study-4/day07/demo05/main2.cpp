/**
 * 算法概述、内部处理、使用范例
 *
 * (b) find 算法的使用
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const int target_number = 35;

    std::vector<int> numbers = {69, 23, 35, 13, 56};

    std::vector<int>::iterator find_iter = std::find(numbers.begin(), numbers.end(), target_number);

    if (find_iter != numbers.end()) {
        std::cout << "found number " << target_number << std::endl;
    } else {
        std::cout << "not found number " << target_number << std::endl;
    }

    return 0;
}