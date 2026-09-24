/**
 * 函数对象回顾、系统函数对象及范例
 *
 * (a) 自定义的函数对象
 */

#include <algorithm>
#include <iostream>
#include <vector>

class CompareInt {
public:
    bool operator()(const int i, const int j) const {
        // 升序排序（从小到大）
        return i > j;
    }
};

int main() {
    std::vector<int> numbers = {69, 23, 35, 13, 56};

    // 使用自定义的函数对象进行排序，CompareInt() 会生成一个临时对象（可调用对象）
    std::sort(numbers.begin(), numbers.end(), CompareInt());

    for_each(numbers.begin(), numbers.end(), [](const int& number) { std::cout << number << " "; });

    return 0;
}