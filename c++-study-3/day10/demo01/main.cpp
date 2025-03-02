/**
 * 智能指针基础知识
 */

#include <iostream>
#include <stdexcept>

using namespace std;

// 模拟实现不带引用计数的智能指针，类似 unique_ptr 智能指针
template<typename T>
class CSmartPtr {

public:
    // 构造函数
    CSmartPtr(T *ptr = nullptr) : _ptr(ptr) {
        cout << "CSmartPtr(T *ptr)" << endl;
    }

    // 析构函数
    ~CSmartPtr() {
        cout << "~CSmartPtr()" << endl;
        delete _ptr;
    }

    // 显式删除拷贝构造
    CSmartPtr(const CSmartPtr<T> &) = delete;

    // 显式删除拷贝赋值
    CSmartPtr<T> &operator=(const CSmartPtr<T> &) = delete;

    // 带右值引用参数的拷贝构造函数，支持移动构造（即支持 move 移动语义）
    CSmartPtr(CSmartPtr<T> &&src) noexcept : _ptr(src._ptr) {
        cout << "CSmartPtr(CSmartPtr<T> &&src)" << endl;
        src._ptr = nullptr;
    }

    // 带右值引用参数的赋值运算符重载函数，支持移动赋值（即支持 move 移动语义）
    CSmartPtr<T> &operator=(CSmartPtr<T> &&src) noexcept {
        cout << "CSmartPtr<T> &operator=(CSmartPtr<T> &&src)" << endl;
        // 避免自赋值
        if (this == &src) {
            return *this;
        }

        // 先存储当前的指针，避免删除自己后 src._ptr 变为 nullptr
        T *old_ptr = _ptr;

        // 转移所有权
        _ptr = src._ptr;
        src._ptr = nullptr;

        // 释放旧资源
        delete old_ptr;

        return *this;
    }

    // * 运算符重载函数
    T &operator*() {
        if (!_ptr) {
            throw runtime_error("Dereferencing a null pointer!");
        }
        return *_ptr;
    }

    // -> 运算符重载函数
    T *operator->() {
        if (!_ptr) {
            throw runtime_error("Accessing member of a null pointer!");
        }
        return _ptr;
    }

    // 释放所有权，不删除对象
    T *release() noexcept {
        T *temp = _ptr;
        _ptr = nullptr;
        return temp;
    }

    // 重新分配资源
    void reset(T *ptr = nullptr) noexcept {
        // 避免 delete 自己的对象
        if (_ptr == ptr) {
            return;
        }

        delete _ptr;
        _ptr = ptr;
    }

    // 获取原始指针
    T *get() const noexcept {
        return _ptr;
    }

private:
    T *_ptr;
};


void test01() {
    CSmartPtr<int> ptr1(new int(30));
    // CSmartPtr<int> ptr2(ptr1);         // 编译出错，不可复制
}

void test02() {
    CSmartPtr<int> ptr1(new int(30));
    CSmartPtr<int> ptr2(new int(10));
    // ptr2 = ptr1;                         // 编译出错，不可赋值
}

void test03() {
    CSmartPtr<int> ptr1(new int(10));
    CSmartPtr<int> ptr2(move(ptr1));      // 支持移动构造，将 ptr1 的所有权转移到 ptr2，ptr1 变为空
    // cout << *ptr1 << endl;              // 程序运行出错，试图解引用 ptr1，会导致未定义行为
    cout << *ptr2 << endl;                 // 正常输出 10
}

void test04() {
    CSmartPtr<int> ptr1(new int(30));
    CSmartPtr<int> ptr2(new int(10));
    ptr2 = move(ptr1);                     // 支持移动赋值，将 ptr1 的所有权转移到 ptr2，ptr1 变为空
    // cout << *ptr1 << endl;              // 程序运行出错，试图解引用 ptr1，会导致未定义行为
    cout << *ptr2 << endl;                 // 正常输出 30
}

void test05() {
    CSmartPtr<int> p1(new int(10));
    int *rawPtr = p1.release();             // p1 不再管理该资源
    delete rawPtr;                          // 需要手动释放

    CSmartPtr<int> p2;
    p2.reset(new int(20));               // 重新分配资源
}
