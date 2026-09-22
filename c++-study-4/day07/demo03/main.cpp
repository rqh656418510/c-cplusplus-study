/**
 * 分配器概述、使用，工作原理说
 *
 * (a) std::allocator 的使用
 */

#include <iostream>
#include <list>

int main() {
    std::list<int> myList1;

    // 等效于上面的写法
    std::list<int, std::allocator<int>> myList2;

    for (int i = 0; i < 5; ++i) {
        myList2.push_back(i);
    }

    for (int& iter : myList2) {
        std::cout << &iter << std::endl;
    }

    return 0;
}