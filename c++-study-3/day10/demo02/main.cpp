/**
 * 不带引用计数的智能指针
 */

#include <iostream>
#include <memory>

using namespace std;

void test01() {
    auto_ptr<int> ptr1(new int(20));   // ptr1 拥有这个动态分配的 int(20)
    auto_ptr<int> ptr2(ptr1);          // ptr1 的所有权被 ptr2 接管，ptr1 变为空
    *ptr2 = 10;                        // 通过 ptr2 修改资源的值
    // cout << *ptr1 << endl;          // 程序运行出错，试图解引用 ptr1，会导致未定义行为
	cout << *ptr2 << endl;             // 正常输出 10
}

void test02() {
    auto_ptr<int> ptr1(new int(20));   // ptr1 拥有这个动态分配的 int(20)
    auto_ptr<int> ptr2(new int(30));   // ptr2 拥有这个动态分配的 int(30)
    ptr2 = ptr1;                       // ptr1 的所有权被 ptr2 接管，ptr1 变为空
    // cout << *ptr1 << endl;          // 程序运行出错，试图解引用 ptr1，会导致未定义行为
    cout << *ptr2 << endl;             // 正常输出 20
}

////////////////////////////////////////////////////////////////////////

void test03() {
    unique_ptr<int> ptr1(new int(30));
    // unique_ptr<int> ptr2(ptr1);         // 编译出错，不可复制
}

void test04() {
    unique_ptr<int> ptr1(new int(30));
    unique_ptr<int> ptr2(new int(10));
    // ptr2 = ptr1;                         // 编译出错，不可赋值
}

void test05() {
    unique_ptr<int> ptr1(new int(10));
    unique_ptr<int> ptr2(move(ptr1));      // 支持移动构造，将 ptr1 的所有权转移到 ptr2，ptr1 变为空
    // cout << *ptr1 << endl;              // 程序运行出错，试图解引用 ptr1，会导致未定义行为
    cout << *ptr2 << endl;                 // 正常输出 10
}

void test06() {
    unique_ptr<int> ptr1(new int(30));
    unique_ptr<int> ptr2(new int(10));
    ptr2 = move(ptr1);                     // 支持移动赋值，将 ptr1 的所有权转移到 ptr2，ptr1 变为空
    // cout << *ptr1 << endl;              // 程序运行出错，试图解引用 ptr1，会导致未定义行为
    cout << *ptr2 << endl;                 // 正常输出 30
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
}