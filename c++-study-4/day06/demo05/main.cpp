/**
 * 重载全局new、delete，定位new及重载等
 *
 * (a) 重载全局 new、delete 运算符
 */

#include <cstdlib>
#include <iostream>

// 重载全局 new 运算符，用于对象分配内存
void* operator new(size_t size) {
    return malloc(size);
}

// 重载全局 delete 运算符，用于对象释放内存
void operator delete(void* ptr) {
    free(ptr);
}

// 全局重载 new[] 运算符，用于数组分配内存
void* operator new[](size_t size) {
    return malloc(size);
}

// 全局重载 delete[] 运算符，用于数组释放内存
void operator delete[](void* ptr) {
    free(ptr);
}

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass::MyClass()" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass::~MyClass()" << std::endl;
    }

private:
    int m_i = 0;
};

int main() {
    int* p_int = new int(12);
    delete p_int;

    char* p_chars = new char[3];
    delete[] p_chars;

    MyClass* p_obj = new MyClass();
    delete p_obj;

    MyClass* p_obj_arr = new MyClass[2];
    delete[] p_obj_arr;

    return 0;
}