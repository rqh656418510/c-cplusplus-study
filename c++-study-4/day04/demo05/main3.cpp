/**
 * shared_ptr使用场景、陷阱、性能分析、使用建议
 *
 * (c) shared_ptr 的性能分析
 */

#include <iostream>
#include <memory>

using namespace std;

// shared_ptr 的大小是裸指针的两倍
void test01() {
    int *p;
    shared_ptr<int> wp;
    int length1 = sizeof(p);   // 8 个字节（64 位系统）
    int length2 = sizeof(wp);  // 16 个字节（64 位系统）
    cout << length1 << endl;
    cout << length2 << endl;
}

// shared_ptr 的移动语义
void test02() {
    shared_ptr<int> sp = make_shared<int>(100);
    shared_ptr<int> sp2 = (move(sp));  // 移动构造一个新的 shared_ptr 对象 sp2
    cout << sp2.use_count() << endl;   // sp 不再指向原对象（置为空），但原对象的引用计数仍然是 1

    shared_ptr<int> sp3;
    sp3 = move(sp2);                  // 移动赋值
    cout << sp3.use_count() << endl;  // sp2 不再指向原对象（置为空），但原对象的引用计数仍然是 1
}

int main() {
    test01();
    test02();
    return 0;
}