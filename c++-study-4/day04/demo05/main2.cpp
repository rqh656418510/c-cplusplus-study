/**
 * shared_ptr使用场景、陷阱、性能分析、使用建议
 *
 * (b) shared_ptr 的使用陷阱
 */

#include <iostream>
#include <memory>

using namespace std;

void proc(shared_ptr<int> sp) {
    return;
}

int main() {
    int *p = new int(100);     // 裸指针
    proc(shared_ptr<int>(p));  // 使用 shared_ptr 临时对象作为函数参数
    *p = 45;                   // 错误写法（存在未定义行为），因为 proc() 执行结束后，p 指向的内存已经被 shared_ptr 临时对象释放掉
    return 0;
}