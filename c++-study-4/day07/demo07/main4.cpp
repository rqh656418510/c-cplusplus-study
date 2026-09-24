/**
 * 适配器概念、分类、范例及总结
 *
 * (d) 迭代器适配器的使用
 */

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> src = {"apple", "banana", "cherry"};

    // 使用 move_iterator 包装 std::vector 的迭代器，将 std::vector<std::string> 中的元素 "搬" 到另一个 vector，而不是逐个拷贝字符串
    std::vector<std::string> dst(std::make_move_iterator(src.begin()), std::make_move_iterator(src.end()));

    // 遍历 dst 中的所有元素
    std::cout << "dst: ";
    for (const auto& s : dst) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    // src 里的字符串内容被 "搬走" 后，通常变成空串（具体内容取决于实现，标准只保证 "有效但未指定"）
    std::cout << "src after move: ";
    for (const auto& s : src) {
        std::cout << "[" << s << "] ";
    }
    std::cout << std::endl;

    return 0;
}