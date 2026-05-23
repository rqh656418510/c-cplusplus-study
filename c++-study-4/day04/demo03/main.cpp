/**
 * shared_ptr常用操作、计数、自定义删除器等等
 *
 * <a> shared_ptr 常用操作
 */

#include <iostream>
#include <memory>

using namespace std;

void test01() {
    shared_ptr<int> sp = make_shared<int>(100);
    shared_ptr<int> sp2(sp);  // 智能指针 sp 与 sp2 指向同一个对象
}

// use_count()
void test02() {
    shared_ptr<int> sp = make_shared<int>(100);
    int count1 = sp.use_count();
    cout << count1 << endl;  // 输出 1

    shared_ptr<int> sp2(sp);
    int count2 = sp.use_count();
    cout << count2 << endl;  // 输出 2

    shared_ptr<int> sp3;
    sp3 = sp;
    int count3 = sp.use_count();
    cout << count3 << endl;  // 输出 3
}

// unique()
void test03() {
    shared_ptr<int> sp = make_shared<int>(100);
    cout << sp.unique() << endl;  // 输出 1，表示 true

    shared_ptr<int> sp2(sp);
    cout << sp.unique() << endl;  // 输出 0，表示 false
}

// reset()
void test04() {
    shared_ptr<int> sp = make_shared<int>(100);
    shared_ptr<int> sp2 = sp;  // 引用计数为 2
    sp.reset();                // 非唯一指向时：不释放原对象的内存，引用计数减为 1，p1 置空，此时 p2 仍有效
    sp2.reset();               // 唯一指向时：释放原对象的内存，引用计数减为 0，p2 置空
}

// reset()
void test05() {
    auto p1 = std::make_shared<int>(100);  // 对象 A
    auto p2 = p1;                          // 对象 A，引用计数为 2

    // 情况1：非唯一指向
    p1.reset(new int(200));  // 对象 A 的引用计数减为 1（不释放原对象内存），p1 现在指向新对象 B(200)，此时 p2 仍指向原对象 A(100) 且有效

    auto p3 = std::make_shared<int>(300);  // 对象 C，引用计数为 1

    // 情况2：唯一指向
    p3.reset(new int(400));  // 对象 C 的引用计数减为 0（释放原对象内存），p3 现在指向新对象 D(400)
}

// reset()
void test06() {
    shared_ptr<int> sp;      // 空指针
    sp.reset(new int(100));  // 空指针也可以通过 reset() 来初始化
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    return 0;
}