#include<iostream>
#include <stdexcept>
#include "ngx_mem_pool.h"

// 构造函数
ngx_mem_pool::ngx_mem_pool(int size) {
    // 创建内存池
    this->ngx_create_pool(size);
    if (_pool == nullptr) {
        throw std::runtime_error("create memory pool fail...");
    }
}

// 析构函数
ngx_mem_pool::~ngx_mem_pool() {
    // 销毁内存池
    if (_pool != nullptr) {
        this->ngx_destroy_pool();
    }
}

// 创建指定大小的内存池
void *ngx_mem_pool::ngx_create_pool(size_t size) {
    if (size < NGX_MIN_POOL_SIZE) {
        std::cout << "create memory pool fail, pool size too small" << std::endl;
        return nullptr;
    }

    // 分配内存空间
    _pool = (ngx_pool_s *) malloc(size);
    if (_pool == nullptr) {
        return nullptr;
    }

    // 小块内存池的头部信息
    _pool->d.last = (u_char *) _pool + sizeof(ngx_pool_s);
    _pool->d.end = (u_char *) _pool + size;
    _pool->d.next = nullptr;
    _pool->d.failed = 0;

    // 小块内存分配的最大空间
    size = size - sizeof(ngx_pool_s);
    _pool->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    _pool->current = _pool;
    _pool->large = nullptr;
    _pool->cleanup = nullptr;

    return _pool;
}

// 从内存池中申请指定大小的内存，并考虑内存字节对齐
void *ngx_mem_pool::ngx_palloc(size_t size) {
    if (size <= this->_pool->max) {
        return ngx_palloc_small(size, 1);
    }
    return ngx_palloc_large(size);
}

// 从内存池中申请指定大小的内存，不考虑内存字节对齐
void *ngx_mem_pool::ngx_pnalloc(size_t size) {
    if (size <= this->_pool->max) {
        return ngx_palloc_small(size, 0);
    }
    return ngx_palloc_large(size);
}

// 调用 ngx_palloc 实现内存分配，并将内存初始化为 0
void *ngx_mem_pool::ngx_pcalloc(size_t size) {
    void *p;

    p = ngx_palloc(size);
    if (p) {
        ngx_memzero(p, size);
    }

    return p;
}

// 分配小块内存
void *ngx_mem_pool::ngx_palloc_small(size_t size, ngx_uint_t align) {
    u_char *m;
    ngx_pool_s *p;

    p = this->_pool->current;

    // 遍历小块内存池链表，查找有可用空间的小块内存
    do {
        m = p->d.last;

        if (align) {
            m = ngx_align_ptr(m, NGX_ALIGNMENT);
        }

        if ((size_t) (p->d.end - m) >= size) {
            p->d.last = m + size;

            return m;
        }

        p = p->d.next;

    } while (p);

    // 当找不到有可用空间的小块内存，则直接分配新的小块内存
    return ngx_palloc_block(size);
}

// 分配大块内存
void *ngx_mem_pool::ngx_palloc_large(size_t size) {
    void *p;
    ngx_uint_t n;
    ngx_pool_large_s *large;

    // 分配新的大块内存
    p = malloc(size);
    if (p == nullptr) {
        return nullptr;
    }

    n = 0;

    // 遍历大块内存池链表，将新的大块内存添加到链表中
    for (large = this->_pool->large; large; large = large->next) {
        if (large->alloc == nullptr) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    large = (ngx_pool_large_s *) ngx_palloc_small(sizeof(ngx_pool_large_s), 1);
    if (large == nullptr) {
        free(p);
        return nullptr;
    }

    large->alloc = p;
    large->next = this->_pool->large;
    this->_pool->large = large;

    return p;
}

// 分配新的小块内存
void *ngx_mem_pool::ngx_palloc_block(size_t size) {
    u_char *m;
    size_t psize;
    ngx_pool_s *p, *_new;

    // 新的小块内存的大小
    psize = (size_t) (this->_pool->d.end - (u_char *) this->_pool);

    // 分配新的小块内存
    m = (u_char *) malloc(psize);
    if (m == nullptr) {
        return nullptr;
    }

    _new = (ngx_pool_s *) m;

    // 新的小块内存的头部信息
    _new->d.end = m + psize;
    _new->d.next = nullptr;
    _new->d.failed = 0;

    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    _new->d.last = m + size;

    for (p = this->_pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            this->_pool->current = p->d.next;
        }
    }

    p->d.next = _new;

    return m;
}

// 释放大块内存
void ngx_mem_pool::ngx_pfree(void *p) {
    ngx_pool_large_s *l;
    for (l = this->_pool->large; l; l = l->next) {
        if (p == l->alloc) {
            free(l->alloc);
            l->alloc = nullptr;
            return;
        }
    }
}

// 重置内存池
void ngx_mem_pool::ngx_reset_pool() {
    ngx_pool_s *p;
    ngx_pool_large_s *l;

    // 释放大块内存池链表中的所有内存
    for (l = this->_pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }

    // 重置小块内存池链表中的第一块内存，实现后续小块内存的复用
    p = this->_pool;
    p->d.last = (u_char *) p + sizeof(ngx_pool_s);
    p->d.failed = 0;


    // 重置小块内存池链表中的第二块到最后一块内存，实现后续小块内存的复用
    for (p = p->d.next; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof(ngx_pool_data_t);
        p->d.failed = 0;
    }

    this->_pool->current = this->_pool;
    this->_pool->large = nullptr;
}

// 销毁内存池
void ngx_mem_pool::ngx_destroy_pool() {
    ngx_pool_s *p, *n;
    ngx_pool_large_s *l;
    ngx_pool_cleanup_s *c;

    // 调用所有清理操作（回调）函数
    for (c = this->_pool->cleanup; c; c = c->next) {
        if (c->handler) {
            c->handler(c->data);
        }
    }

    // 释放大块内存池链表中的所有内存
    for (l = this->_pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }

    // 释放小块内存池链表中的所有内存
    for (p = this->_pool, n = this->_pool->d.next; /* void */; p = n, n = n->d.next) {
        free(p);
        if (n == nullptr) {
            break;
        }
    }
}

// 添加资源清理操作（回调）函数
ngx_pool_cleanup_s *ngx_mem_pool::ngx_pool_cleanup_add(size_t size) {
    ngx_pool_cleanup_s *c;

    c = (ngx_pool_cleanup_s *) ngx_palloc(sizeof(ngx_pool_cleanup_s));
    if (c == nullptr) {
        return nullptr;
    }

    if (size) {
        c->data = ngx_palloc(size);
        if (c->data == nullptr) {
            return nullptr;
        }

    } else {
        c->data = nullptr;
    }

    c->handler = nullptr;

    // 添加到资源清理操作链表中（头插法）
    c->next = this->_pool->cleanup;
    this->_pool->cleanup = c;

    return c;
}