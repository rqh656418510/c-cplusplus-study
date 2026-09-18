/**
 * new细节探秘，重载类operator new delete
 *
 * (b) 重载 new、delete 运算符
 */

#include <cstdlib>
#include <iostream>
#include <new>

using namespace std;

class MyClass {
public:
    // 构造函数
    MyClass() {
        cout << "MyClass() called" << endl;
    }

    // 析构函数
    ~MyClass() {
        cout << "~MyClass() called" << endl;
    }

    // 重载 new 运算符，用于对象分配内存
    static void* operator new(size_t size) {
        cout << "operator new called, size: " << size << endl;
        void* ptr = malloc(size);
        if (!ptr) {
            throw bad_alloc();
        }
        return ptr;
    }

    // 重载 delete 运算符，用于对象释放内存
    static void operator delete(void* ptr) {
        cout << "operator delete called" << endl;
        if (ptr) {
            free(ptr);
        }
    }

    // 重载 new[] 运算符，用于数组分配内存
    static void* operator new[](size_t size) {
        cout << "operator new[] called, size: " << size << endl;
        void* ptr = malloc(size);
        if (!ptr) {
            throw bad_alloc();
        }
        return ptr;
    }

    // 重载 delete[] 运算符，用于数组释放内存
    static void operator delete[](void* ptr) {
        cout << "operator delete[] called" << endl;
        if (ptr) {
            free(ptr);
        }
    }

public:
    int m_i;
};

int main() {
    // 单个对象
    MyClass* mc = new MyClass();
    delete mc;

    cout << "------------------" << endl;

    // 对象数组
    MyClass* marry = new MyClass[3];
    delete[] marry;

    return 0;
}