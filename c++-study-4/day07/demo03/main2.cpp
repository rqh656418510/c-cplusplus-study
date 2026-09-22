/**
 * 分配器概述、使用，工作原理说
 *
 * (b) std::allocator 的使用
 */

#include <iostream>
#include <list>

int main() {
    // 定义一个 allocator 对象，为 int 类型对象分配内存
    std::allocator<int> alloc;

    // 通过 allocate() 分配一段原始的未构造的内存，这段内存能够保存 3 个类型为 int 的对象（12 个字节）
    int* p = alloc.allocate(3);

    // 在这块内存中使用 3 个 int 对象
    int* q = p;
    *q = 1;
    q++;
    *q = 2;
    q++;
    *q = 3;

    // 通过 deallocate() 释放内存，第二个参数必须与 allocate() 的数量对应，记住分配了几个对象的内存，就要正确释放几个对象的内存
    alloc.deallocate(p, 3);

    return 0;
}