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

// 裸指针与智能指针混合使用
void test01() {
    int *p = new int(100);     // 裸指针
    proc(shared_ptr<int>(p));  // 使用 shared_ptr 临时对象作为函数参数
    *p = 45;                   // 错误写法（存在未定义行为），因为 proc() 执行结束后，p 指向的内存已经被 shared_ptr 临时对象释放掉
}

// 使用裸指针初始化多个智能指针
void test02() {
    int *p = new int(100);
    shared_ptr<int> sp1(p);
    shared_ptr<int> sp2(p);  // 错误写法，使用同一个裸指针初始化多个 shared_ptr
    // 离开作用域后，p 指向的内存会被 delete 两次（因为 sp1 与 sp2 的引用计数是互相独立的，没有任何关联关系），导致程序运行崩溃
}

// 谨慎使用 get() 返回的裸指针
void test03() {
    shared_ptr<int> sp = make_shared<int>(100);
    int *p = sp.get();
    // delete p;  // 错误写法，不能将 get() 返回的裸指针 delete 掉，否则会重复释放内存，导致程序运行崩溃
    // shared_ptr<int> sp2(p); // 错误写法，不能将 get() 返回的裸指针绑定到其他 shared_ptr，否则会重复释放内存，导致程序运行崩溃
}

int main() {
    // test01();
    // test02();
    // test03();
    return 0;
}
