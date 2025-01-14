/**
 * 深入理解new的delete的原理
 *
 * <p> 生成汇编代码：g++ -S -o main.s main.cpp
 */

#include <iostream>

using namespace std;

// 重写 new 运算符，先调用 operator new 开辟内存空间，然后再调用对象的构造函数（初始化）
void *operator new(size_t size) {
    void *ptr = malloc(size);
    if (ptr == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new address: " << ptr << endl;
    return ptr;
}

// 重写 delete 运算符，先调用 ptr 指向对象的析构函数，然后再调用 operator delete 释放内存空间
void operator delete(void *ptr) {
    if (ptr != nullptr) {
        free(ptr);
        cout << "operator delete address: " << ptr << endl;
    }
}

// 重写 new[] 运算符，先调用 operator new 开辟内存空间，然后再调用对象的构造函数（初始化）
void *operator new[](size_t size) {
    void *ptr = malloc(size);
    if (ptr == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new[] address: " << ptr << endl;
    return ptr;
}

// 重写 delete[] 运算符，先调用 ptr 指向对象的析构函数，然后再调用 operator delete 释放内存空间
void operator delete[](void *ptr) {
    if (ptr != nullptr) {
        free(ptr);
        cout << "operator delete[] address: " << ptr << endl;
    }
}

class Test {
public:
    Test(int data = 10) : _data(data) {
        cout << "Test()" << endl;
    }

    ~Test() {
        cout << "~Test()" << endl;
    }

private:
    int _data;
};

void test01() {
    cout << "============ test01() ============" << endl;
    try {
        // 调用重载后的 new 和 delete 运算符
        int *p = new int;
        delete p;
    } catch (const bad_alloc &exception) {
        cerr << exception.what() << endl;
    }
}

void test02() {
    cout << "============ test02() ============" << endl;
    try {
        // 调用重载后的 new[] 和 delete[] 运算符
        int *p = new int[10];
        delete[] p;
    } catch (const bad_alloc &exception) {
        cerr << exception.what() << endl;
    }
}

void test03() {
    cout << "============ test03() ============" << endl;
    try {
        // 调用重载后的 new 和 delete 运算符
        Test *t = new Test(5);
        delete t;
    } catch (const bad_alloc &exception) {
        cerr << exception.what() << endl;
    }
}

void test04() {
    cout << "============ test04() ============" << endl;
    try {
        // 调用重载后的 new[] 和 delete[] 运算符
        Test *t = new Test[2]();
        delete[] t;
    } catch (const bad_alloc &exception) {
        cerr << exception.what() << endl;
    }
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}
