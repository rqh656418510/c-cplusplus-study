/**
 * 可变参数函数、initializer_list、省略号形参
 *
 * (b) initializer_list
 */

#include <initializer_list>
#include <iostream>

// std::initializer_list 初始化
void test01() {
    std::initializer_list<int> list;               // 空列表（空数组）
    std::initializer_list<int> list2 = {1, 2, 3};  // 数组，元素类型是 int
}

// std::initializer_list 遍历
void test02() {
    std::initializer_list<int> list = {1, 2, 3};  // 数组，元素类型是 int
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    test01();
    test02();
    return 0;
}