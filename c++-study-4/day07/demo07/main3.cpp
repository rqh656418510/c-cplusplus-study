/**
 * 适配器概念、分类、范例及总结
 *
 * (c) 算法适配器（函数适配器）的使用
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {50, 16, 80, 25, 46, 80};

    // 统计值小于 40 的元素个数
    // std::bind 会生成一个新的可调用对象（函数对象）：调用它时，传入的第 1 个实参传给 std::less<int> 的第 1 个参数，std::less<int> 的第 2 个参数固定绑定为 40，因此等价于判断 "元素 < 40"
    const size_t less_total = std::count_if(vec.begin(), vec.end(), std::bind(std::less<int>(), std::placeholders::_1, 40));
    std::cout << "less total: " << less_total << std::endl;

    // 统计值大于 40 的元素个数
    // std::bind 会生成一个新的可调用对象（函数对象）：调用它时，传入的第 1 个实参传给 std::greater<int> 的第 1 个参数，std::greater<int> 的第 2 个参数固定绑定为 40，因此等价于判断 "元素 > 40"
    const size_t greater_total = std::count_if(vec.begin(), vec.end(), std::bind(std::greater<int>(), std::placeholders::_1, 40));
    std::cout << "greater total: " << greater_total << std::endl;

    return 0;
}