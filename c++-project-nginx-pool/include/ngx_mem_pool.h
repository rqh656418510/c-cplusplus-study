#pragma once

#include <string.h>

// 将数值 d 调整为临近数值 a 的倍数
#define ngx_align(d, a) (((d) + (a - 1)) & ~(a - 1))

// 将数值 p 调整为临近数值 a 的倍数
#define ngx_align_ptr(p, a) (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

// 将指定的内存全部初始化为0
#define ngx_memzero(buf, n) (void) memset(buf, 0, n)

// 类型重定义
using u_char = unsigned char;
using ngx_uint_t = unsigned int;

// 类型前置声明
struct ngx_pool_s;

// 清理函数（回调函数）的类型
typedef void (*ngx_pool_cleanup_pt)(void *data);

// 清理操作的头部信息
struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt handler;     // 函数指针，指向内存清理操作的回调函数
    void *data;                      // 传递给回调函数的参数
    ngx_pool_cleanup_s *next;        // 下一个清理函数，最终形成单向链表
};

// 大块内存的内存池的头部信息
struct ngx_pool_large_s {
    ngx_pool_large_s *next;      // 下一个大块内存，最终形成单向链表
    void *alloc;                 // 记录分配的大块内存的起始地址
};

// 小块内存的内存池的头部信息
struct ngx_pool_data_t {
    u_char *last;           // 可分配内存的开始位置，即当前内存分配结束位置
    u_char *end;            // 可分配内存的末尾位置
    ngx_pool_s *next;       // 链接到下一个内存池，内存池的很多块内存就是通过该指针连接成链表的
    ngx_uint_t failed;      // 记录当前内存池分配内存失败的次数，当失败次数大于指定值时，current 指向下一内存池单元
};

// 内存池的主结构体
struct ngx_pool_s {
    ngx_pool_data_t d;              // 小块内存池的头部信息
    size_t max;                     // 小块内存分配的最大空间
    ngx_pool_s *current;            // 指向内存池中的可用内存块
    ngx_pool_large_s *large;        // 大块内存分配入口指针，大块内存分配直接采用标准系统接口 malloc()
    ngx_pool_cleanup_s *cleanup;    // 清理函数 handler 的入口指针，用于指定内存释放时需要清理资源的一些必要操作
};

// 一个物理页面的默认大小（4KB）
const int NGX_PAGESIZE = 4096;
// 小块内存可分配的最大空间
const int NGX_MAX_ALLOC_FROM_POOL = NGX_PAGESIZE - 1;
// 内存池的默认初始大小（16KB）
const int NGX_DEFAULT_POOL_SIZE = 16 * 1024;
// 内存池分配时的对齐字节数（16 字节）
const int NGX_POOL_ALIGNMENT = 16;
// 小块内存的最小可接受大小
const int NGX_MIN_POOL_SIZE = ngx_align((sizeof(ngx_pool_s) + 2 * sizeof(ngx_pool_large_s)), NGX_POOL_ALIGNMENT);
// 小块内存分配时的对齐字节数，通常是 4 字节（32 位系统）或者 8 字节（64 位系统）
const int NGX_ALIGNMENT = sizeof(unsigned long);

class ngx_mem_pool {

public:
    // 构造函数
    ngx_mem_pool(int size = NGX_DEFAULT_POOL_SIZE);

    // 析构函数
    ~ngx_mem_pool();

    // 禁止拷贝
    ngx_mem_pool(const ngx_mem_pool &pool) = delete;

    // 禁止赋值
    ngx_mem_pool &operator=(const ngx_mem_pool &) = delete;

public:
    // 从内存池中申请指定大小的内存，并考虑内存字节对齐
    void *ngx_palloc(size_t size);

    // 从内存池中申请指定大小的内存，不考虑内存字节对齐
    void *ngx_pnalloc(size_t size);

    // 调用 ngx_palloc 实现内存分配，并将内存初始化为 0
    void *ngx_pcalloc(size_t size);

    // 释放大块内存
    void ngx_pfree(void *p);

    // 重置内存池
    void ngx_reset_pool();

    // 销毁内存池
    void ngx_destroy_pool();

    // 添加资源清理操作（回调）函数
    ngx_pool_cleanup_s *ngx_pool_cleanup_add(size_t size);

private:
    // 创建指定大小的内存池
    void *ngx_create_pool(size_t size);

    // 分配小块内存
    void *ngx_palloc_small(size_t size, ngx_uint_t align);

    // 分配大块内存
    void *ngx_palloc_large(size_t size);

    // 分配新的小块内存
    void *ngx_palloc_block(size_t size);

private:
    // 指向内存池的入口指针
    ngx_pool_s *_pool;

};