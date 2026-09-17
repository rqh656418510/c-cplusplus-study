/**
 * 嵌入式指针概念及范例、内存池改进版
 *
 * (c) 使用嵌入指针 + 宏定义优化内存池
 */

#include <cstdlib>
#include <iostream>
#include <new>
#include <vector>

// 内存池类
class MyAllocator {
public:
    // 析构函数
    ~MyAllocator() {
        // 释放所有已分配的内存空间
        for (void* memory_block : m_memory_blocks) {
            free(memory_block);
        }
    }

    // 分配内存
    void* allocate(size_t size) {
        // 要求每个内存块至少要能够存放 Object 中的 next 嵌入式指针
        if (size < sizeof(Object)) {
            throw std::bad_alloc();
        }

        Object* tmplink;

        // 分配内存空间
        if (m_free_posi == nullptr) {
            // 计算真正需要分配的内存大小
            size_t real_size = size * m_trunk_count;

            // 调用 malloc() 真正分配内存
            void* memory_block = (Object*)malloc(real_size);

            // 判断内存是否分配成功
            if (memory_block == nullptr) {
                throw std::bad_alloc();
            }

            // 记录调用 malloc() 返回的原始内存地址
            m_memory_blocks.push_back(memory_block);

            m_free_posi = (Object*)memory_block;

            tmplink = m_free_posi;

            // 将分配出来的这一大块内存（由多个小块内存组成）链接起来，供后续使用
            for (int i = 0; i < m_trunk_count - 1; ++i) {
                tmplink->next = (Object*)((char*)tmplink + size);
                tmplink = tmplink->next;
            }

            // 最后一块空闲内存没有指向下一块空闲内存
            tmplink->next = nullptr;
        }

        // 记录准备分配出去的内存的首地址
        tmplink = m_free_posi;

        // 指向下一块可以分配出去的内存（空闲内存）的首地址
        m_free_posi = m_free_posi->next;

        return tmplink;
    }

    // 回收内存空间
    void deallocate(void* phead) {
        if (phead == nullptr) {
            return;
        }

        // 将释放的内存重新加入空闲链表
        Object* p = (Object*)phead;

        p->next = m_free_posi;

        // m_free_posi 总是指向一块可以分配出去的内存（空闲内存）的首地址
        m_free_posi = p;
    }

private:
    // 声明在类的内部，让其只能在类内使用
    struct Object {
        struct Object* next;  // 嵌入式指针（64 位环境下，一个指针本身占用 8 个字节）
    };

    size_t m_trunk_count = 5;            // 一次分配多少倍的该类内存
    Object* m_free_posi = nullptr;       // 总是指向一块可以分配出去的内存（空闲内存）的首地址
    std::vector<void*> m_memory_blocks;  // 保存每次调用 malloc() 返回的原始内存地址
};

/////////////////////////////////////////////////////////////////////////////////////////

// 宏定义 - 声明内存池
#define DECLARE_POOL_ALLOCATOR()         \
public:                                  \
    static MyAllocator allocator;        \
    void* operator new(size_t size) {    \
        return allocator.allocate(size); \
    }                                    \
    void operator delete(void* p) {      \
        allocator.deallocate(p);         \
    }

// 宏定义 - 定义内存池
#define IMPLEMENT_POOL_ALLOCATOR(ClassName) \
    MyAllocator ClassName::allocator;       \

/////////////////////////////////////////////////////////////////////////////////////////

// 普通类
class Student {
    DECLARE_POOL_ALLOCATOR()
private:
    int age = 0;
    int code = 0;
};

IMPLEMENT_POOL_ALLOCATOR(Student)

int main() {
    Student* students[100];

    for (int i = 0; i < 10; ++i) {
        students[i] = new Student();
        std::cout << students[i] << std::endl;
    }

    for (int i = 0; i < 10; ++i) {
        delete students[i];
    }

    return 0;
}