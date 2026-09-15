/**
 * 内存池概念、代码实现和详细分析
 */

#include <cstddef>
#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass::MyClass()" << std::endl;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

    static void* operator new(std::size_t size);

    static void operator delete(void* phead);

    static int m_new_count;  // 创建对象计数统计，每 new 一次就统计一次

    static int m_malloc_count;  // 内存分配计数统计，每 malloc() 一次就统计一次

private:
    MyClass* m_next;  // 指向下一块空闲内存

    static MyClass* m_free_posi;  // 总是指向一块可以分配出去的内存（空闲内存）的首地址

    static int m_trunk_count;  // 一次分配多少倍的该类内存
};

// 静态成员初始化
int MyClass::m_new_count = 0;
int MyClass::m_malloc_count = 0;
MyClass* MyClass::m_free_posi = nullptr;
int MyClass::m_trunk_count = 5;  // 一次分配 5 倍的该类内存作为内存池的大小

void* MyClass::operator new(std::size_t size) {
    MyClass* tmplink;

    // 分配内存
    if (m_free_posi == nullptr) {
        // 计算真正需要分配的内存大小
        size_t realsize = size * m_trunk_count;

        // 调用传统的 new 操作，底层会调用 malloc() 分配内存
        m_free_posi = reinterpret_cast<MyClass*>(new char[realsize]);

        tmplink = m_free_posi;

        // 将分配出来的这一大块内存（由多个小块内存组成）链接起来，供后续使用
        for (int i = 0; i < m_trunk_count - 1; ++i) {
            tmplink->m_next = tmplink + 1;
            ++tmplink;
        }

        // 最后一块内存没有下一块空闲内存
        tmplink->m_next = nullptr;

        // 内存分配计数统计
        ++m_malloc_count;
    }

    // 记录准备分配出去的内存的首地址
    tmplink = m_free_posi;

    // 指向下一块可以分配出去的内存（空闲内存）的首地址
    m_free_posi = m_free_posi->m_next;

    // 创建对象计数统计
    ++m_new_count;

    return tmplink;
}

void MyClass::operator delete(void* phead) {
    if (phead == nullptr) {
        return;
    }

    // 将释放的内存重新加入空闲链表
    MyClass* p = static_cast<MyClass*>(phead);

    p->m_next = m_free_posi;

    // m_free_posi 总是指向一块可以分配出去的内存（空闲内存）的首地址
    m_free_posi = p;
}

int main() {
    MyClass* p1 = new MyClass;
    MyClass* p2 = new MyClass;
    MyClass* p3 = new MyClass;
    MyClass* p4 = new MyClass;
    MyClass* p5 = new MyClass;

    delete p1;
    delete p2;

    MyClass* p6 = new MyClass;
    MyClass* p7 = new MyClass;

    delete p3;
    delete p4;
    delete p5;
    delete p6;
    delete p7;

    std::cout << "new count: " << MyClass::m_new_count << std::endl;
    std::cout << "malloc count: " << MyClass::m_malloc_count << std::endl;

    return 0;
}