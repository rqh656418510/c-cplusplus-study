/**
 * 迭代器的概念和分类
 *
 * (a) 迭代器的使用
 */

#include <iostream>
#include <vector>

void fun1() {
    std::vector<int> v = {1, 2, 3};

    // 可读写正向迭代器
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        // 可以更改元素值
        *it = *it * 2;
        std::cout << *it << std::endl;
    }
}

void fun2() {
    std::vector<int> v = {1, 2, 3};

    // 只读正向迭代器
    for (std::vector<int>::const_iterator it = v.cbegin(); it != v.cend(); ++it) {
        // 不可以更改元素值
        std::cout << *it << std::endl;
    }
}

void fun3() {
    std::vector<int> v = {1, 2, 3};

    // 可读写反向迭代器
    for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        // 可以更改元素值
        *it = *it * 2;
        std::cout << *it << std::endl;
    }
}

void fun4() {
    std::vector<int> v = {1, 2, 3};

    // 只读反向迭代器
    for (std::vector<int>::const_reverse_iterator it = v.crbegin(); it != v.crend(); ++it) {
        // 不可以更改元素值
        std::cout << *it << std::endl;
    }
}

int main() {
    fun1();
    std::cout << "--------------------------" << std::endl;
    fun2();
    std::cout << "--------------------------" << std::endl;
    fun3();
    std::cout << "--------------------------" << std::endl;
    fun4();
    return 0;
}