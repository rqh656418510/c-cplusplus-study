/**
 * 范围for、new内存动态分配、nullptr
 */

#include <iostream>
#include <vector>

// 范围 for
void test01() {
    // 遍历数组
    int arr[] = {1, 2, 3, 4, 5};
    for (int item : arr) {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    // 遍历容器
    std::vector<int> v = {6, 7, 8, 9, 10};
    for (int item : v) {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    // 引用遍历（避免拷贝）- 如果元素是大对象，或需要修改元素，建议用引用
    for (int &item : v) {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    // 引用遍历（避免拷贝）- 如果不想修改元素但又不想拷贝，可以用 `const&`
    for (const int &item : v) {
        std::cout << item << " ";
    }
}

// 动态内存分配
void test02() {

}

int main() {
    test01();
    test02();
    return 0;
}