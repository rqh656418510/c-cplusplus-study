/**
 * 返回unique_ptr、删除器、尺寸、智能指针
 */

#include <iostream>
#include <memory>

using namespace std;

unique_ptr<int> func() {
    unique_ptr<int> up(new int(100));
    return up;  // 返回一个局部对象，编译器会生成一个临时对象，并调用 unique_ptr 的移动构造函数
}

// 返回 unique_ptr 类型
void test01() {
    unique_ptr<int> up = func();  // 接收函数返回的 unique_ptr，调用 unique_ptr 的拷贝构造函数

    unique_ptr<int> up2;  // 接收函数返回的 unique_ptr
    up2 = func();         // 调用 unique_ptr 的赋值运算符
}

void myDeleter(int *p) {
    delete p;
}

// 自定义删除器
void test02() {
    unique_ptr<int, void (*)(int *)> up(new int(100), [](int *p) {
        delete p;
        cout << "delete int *" << endl;
    });
}

int main() {
    test01();
    test02();
    return 0;
}