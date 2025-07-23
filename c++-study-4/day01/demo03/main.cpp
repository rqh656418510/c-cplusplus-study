/**
 * 范围for、new内存动态分配、nullptr
 */

#include <iostream>
#include <vector>
#include <cstring>

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

    std::cout << std::endl;
}

// 动态内存分配
void test02() {
    // malloc() 与 free()
    int *p = nullptr;
    p = (int *) malloc(sizeof(int));
    if (p != nullptr) {
        *p = 5;
        std::cout << *p << std::endl;
        free(p);
    }

    // malloc() 与 free()
    char *c = nullptr;
    const int size = sizeof(char) * 20;
    c = (char *) malloc(size);
    if (c != nullptr) {
        memset(c, 0, size);    // 建议初始化内存（防止访问越界），char 类型值为 0 时，就等于 '\0' 字符
        strcpy(c, "hello world");
        std::cout << c << std::endl;
        free(c);
    }

}

int main() {
    test01();
    test02();
    return 0;
}