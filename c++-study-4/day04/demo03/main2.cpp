/**
 * shared_ptr常用操作、计数、自定义删除器等等
 *
 * (b) 自定义删除器以及数组使用问题
 */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void deleter(int *p) {
    delete p;
    cout << "delete int *" << endl;
}

// 自定义删除器
void test01() {
    // 这里不能使用 make_shared，因为它不支持自定义删除器
    shared_ptr<int> sp(new int(100), deleter);
    sp.reset();  // 唯一指向时：释放原对象的内存（会调用自定义删除器），引用计数减为 0，sp 置空
}

// 自定义删除器
void test02() {
    // 自定义的删除器还可以是 Lamba 表达式
    shared_ptr<int> sp(new int(100), [](int *p) {
        delete p;
        cout << "delete int *" << endl;
    });
}

class MyClass {
public:
    MyClass() {
    }
    ~MyClass() {
        cout << "~MyClass()" << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 解决使用数组的问题
void test03() {
    // 如果 shared_ptr 指向的是数组，那么就需要自定义删除器，否则不会使用 delete [] 正确释放数组的内存
    shared_ptr<MyClass> sp(new MyClass[3], [](MyClass *p) {
        delete[] p;
        cout << "delete MyClass []" << endl;
    });
}

// 使用 default_delete 正确释放数组内存
void test04() {
    // 如果 shared_ptr 指向的是数组，还可以使用 default_delete 来正确释放数组的内存
    shared_ptr<MyClass> sp(new MyClass[3], default_delete<MyClass[]>());
}

// 在 shared_ptr 的 <> 里面加上 []，同样可以正确释放数组内存
void test05() {
    shared_ptr<MyClass[]> sp2(new MyClass[3]);
}

// 函数模板
template <typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

// 函数模板使用
void test06() {
    // 调用自定义的函数模板
    shared_ptr<MyClass> sp = make_shared_array<MyClass>(3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 如果两个 shared_ptr 指定了不同的删除器，只要它们所指向的对象类型相同，那么这两个 shared_ptr 也属于同一种类型
void test07() {
    auto lamba1 = [](int *p) {
        delete p;
        cout << "delete by lamba1" << endl;
    };

    auto lamba2 = [](int *p) {
        delete p;
        cout << "delete by lamba2" << endl;
    };

    shared_ptr<int> p1(new int(100), lamba1);

    shared_ptr<int> p2(new int(200), lamba2);

    // 类型相同，就可以放入到元素类型为该对象类型的容器里面
    // vector<shared_ptr<int>> vec{p1, p2};

    p2 = p1;  // p2 先调用 lamba2 释放自己所指向的对象，然后 p2 重新指向 p1 所指向的对象，此时 p1 所指向对象的引用计数为 2
              // 当作用域结束后，最终还会调用 lamba1 释放 p1、p2 共同指向的对象
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    return 0;
}