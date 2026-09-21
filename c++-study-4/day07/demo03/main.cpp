/**
 * 分配器概述、使用，工作原理说
 */

#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList;

    // 等效于上面的写法
    list<int, allocator<int>> myList2;

    // 10:28

    return 0;
}