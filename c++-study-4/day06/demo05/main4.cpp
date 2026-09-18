/**
 * 重载全局new、delete，定位new及重载等
 *
 * (c) 多种 new 运算符重载
 */

#include <cstdlib>
#include <iostream>
#include <new>

class MyClass {
public:
    MyClass() : m_a(0) {
        std::cout << "MyClass::MyClass()" << std::endl;
    }

    MyClass(const int val) : m_a(val) {
        std::cout << "MyClass::MyClass(const int val)" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass::~MyClass()" << std::endl;
    }

    // 重载 new 运算符
    static void *operator new(size_t size) {
        std::cout << "MyClass::operator new(size_t size)" << std::endl;
        void *ptr = malloc(size);
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    // 重载 new 运算符
    static void *operator new(size_t size, int val) {
        std::cout << "MyClass::operator new(size_t size, int val)" << std::endl;
        void *ptr = malloc(size);
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

private:
    int m_a;
};

int main() {
    MyClass *mc1 = new MyClass();
    delete mc1;

    MyClass *mc2 = new (123) MyClass();
    delete mc2;

    return 0;
}