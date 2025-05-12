#pragma once

#include<mutex>
#include<stdexcept>

// 一级空间配置器，用于分配大块内存
// 封装 malloc() 和 free() 来实现内存管理，可以设置发生 OOM 时释放内存的回调函数
template<int __inst>
class __malloc_alloc_template {

public:

    // 分配内存
    static void *allocate(size_t __n) {
        void *__result = malloc(__n);
        if (nullptr == __result) {
            // 调用OOM处理流程
            __result = _S_oom_malloc(__n);
        }
        return __result;
    }

    // 释放内存
    static void deallocate(void *__p, size_t /* __n */) {
        free(__p);
    }

    // 内存重分配
    static void *reallocate(void *__p, size_t /* old_sz */, size_t __new_sz) {
        void *__result = realloc(__p, __new_sz);
        if (nullptr == __result) {
            // 调用OOM处理流程
            __result = _S_oom_realloc(__p, __new_sz);
        }
        return __result;
    }

    // 设置新的OOM处理函数，返回旧的处理函数
    static void (*__set_malloc_handler(void (*__f)()))() {
        void (*__old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = __f;
        return (__old);
    }

private:

    static void *_S_oom_malloc(size_t);

    static void *_S_oom_realloc(void *, size_t);

    static void (*__malloc_alloc_oom_handler)();

};

// 初始化类静态成员变量
template<int __inst>
void (*__malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = nullptr;

template<int __inst>
void *__malloc_alloc_template<__inst>::_S_oom_malloc(size_t __n) {
    void (*__my_malloc_handler)();
    void *__result;

    // 死循环
    for (;;) {
        __my_malloc_handler = __malloc_alloc_oom_handler;
        if (nullptr == __my_malloc_handler) { throw std::bad_alloc(); }
        // 调用OOM回调函数
        (*__my_malloc_handler)();
        // 再次尝试申请内存
        __result = malloc(__n);
        if (__result) return (__result);
    }
}

template<int __inst>
void *__malloc_alloc_template<__inst>::_S_oom_realloc(void *__p, size_t __n) {
    void (*__my_malloc_handler)();
    void *__result;

    // 死循环
    for (;;) {
        __my_malloc_handler = __malloc_alloc_oom_handler;
        if (nullptr == __my_malloc_handler) { throw std::bad_alloc(); }
        // 调用OOM回调函数
        (*__my_malloc_handler)();
        // 再次尝试内存重分配
        __result = realloc(__p, __n);
        if (__result) return (__result);
    }
}

// 重定义类型
typedef __malloc_alloc_template<0> malloc_alloc;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 二级空间配置器，用于分配小块内存
// 采用基于自由链表原理的内存池机制来实现内存管理
template<typename T>
class __default_alloc_template {

public:

    // 重定义类型
    using value_type = T;

    // 构造函数
    constexpr __default_alloc_template() noexcept {}

    // 拷贝构造函数
    constexpr __default_alloc_template(const __default_alloc_template &) noexcept = default;

    // 模板构造函数
    template<class _Other>
    constexpr __default_alloc_template(const __default_alloc_template<_Other> &) noexcept {}

    // 开辟内存空间
    T *allocate(size_t __n) {
        // 申请内存的总字节数
        __n = __n * sizeof(T);

        void *__ret = nullptr;

        // 分配大块内存
        if (__n > (size_t) _MAX_BYTES) {
            // 采用一级空间配置器分配大内存
            __ret = malloc_alloc::allocate(__n);
        }
            // 分配小块内存
        else {
            // 获取对应大小的自由链表
            _Obj *volatile *__my_free_list = _S_free_list + _S_freelist_index(__n);

            // 获取对应大小的自由链表的互斥锁
            std::lock_guard<std::mutex> __lock_instance(_S_free_list_mtx[_S_freelist_index(__n)]);

            // 获取自由链表的头节点
            _Obj *__result = *__my_free_list;
            if (__result == nullptr)
                // 如果头节点为空（即没有空闲的内存 chunk 块），则分配新的 chunk 块
                __ret = _S_refill(_S_round_up(__n));
            else {
                // 将自由链表的头节点指向下一个内存 chunk 块
                *__my_free_list = __result->_M_free_list_link;
                __ret = __result;
            }
        }

        return (T *) __ret;
    }

    // 释放内存空间
    void deallocate(void *__p, size_t __n) {
        // 释放内存的总字节数
        __n = __n * sizeof(T);

        // 大块内存直接交由malloc分配器释放掉
        if (__n > (size_t) _MAX_BYTES) {
            malloc_alloc::deallocate(__p, __n);
        }
            // 小块内存回收到自由链表
        else {
            // 获取对应大小的自由链表
            _Obj *volatile *__my_free_list = _S_free_list + _S_freelist_index(__n);
            _Obj *__q = (_Obj *) __p;

            // 获取对应大小的自由链表的互斥锁
            std::lock_guard<std::mutex> __lock_instance(_S_free_list_mtx[_S_freelist_index(__n)]);

            // 将释放的小块内存插入到自由链表头部（头插法）
            __q->_M_free_list_link = *__my_free_list;
            *__my_free_list = __q;
        }
    }

    // 内存池扩容 / 缩容
    void *reallocate(void *__p, size_t __old_sz, size_t __new_sz) {
        void *__result;
        size_t __copy_sz;

        // 第一种情况：当新旧大小均超过最大内存池处理阈值是，直接调用系统的 realloc()
        if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
            return (realloc(__p, __new_sz));
        }

        // 第二种情况：当新旧内存块在内存池中的对齐后大小相等，则直接复用旧内存块
        if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) {
            return (__p);
        }

        // 第三种情况：需要执行内存重分配
        __result = allocate(__new_sz);    // 申请新内存块（根据内存池策略）
        __copy_sz = __new_sz > __old_sz ? __old_sz : __new_sz;   // 安全拷贝大小（取较小值）
        memcpy(__result, __p, __copy_sz);    // 数据拷贝（仅拷贝有效内容）
        deallocate(__p, __old_sz);     // 释放旧内存块（根据旧内存块的大小进行回收）

        return (__result);
    }

    // 对象构造（利用可变参数模板 + 引用折叠 + 完美转发）
    template<typename... Args>
    void construct(T *__p, Args &&... args) {
        // 在指定的内存构造对象（定位 new）
        new(__p) T(std::forward<Args>(args)...);
    }

    // 对象析构
    void destroy(T *__p) {
        // 在指定的内存析构对象
        __p->~T();
    }

private:

    enum { _ALIGN = 8 };            // 内存对齐粒度（每次分配 8 字节的倍数）
    enum { _MAX_BYTES = 128 };      // 二级空间配置器的最大管理范围（128 字节）
    enum { _NFREELISTS = 16 };      // 自由链表的数量，计算方式：_MAX_BYTES / _ALIGN

    // 每一个内存 chunk 块的头信息
    union _Obj {
        union _Obj* _M_free_list_link;		// 下一个内存 chunk 块的地址
        char _M_client_data[1];				// 实际分配给用户的内存起始位置
    };

    // 记录内存 chunk 块的分配情况
    static char *_S_start_free;
    static char *_S_end_free;
    static size_t _S_heap_size;

    // 组织所有自由链表的数组，数组的每一个元素的类型都是 _Obj*
    static _Obj *volatile _S_free_list[_NFREELISTS];

    // 所有自由链表的互斥锁的数组（内存池基于自由链表实现，需要考虑线程安全问题，为每个自由链表添加一个互斥锁，降低锁的粒度）
    static std::mutex _S_free_list_mtx[_NFREELISTS];

    // 将 __bytes 上调至最邻近的 8 的倍数（实现内存对齐）
    static size_t _S_round_up(size_t __bytes) {
        return (((__bytes) + (size_t) _ALIGN - 1) & ~((size_t) _ALIGN - 1));
    }

    // 返回 __bytes 大小的 chunk 块位于自由链表数组中的索引
    static size_t _S_freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t) _ALIGN - 1) / (size_t) _ALIGN - 1);
    }

    // 分配新的内存 chunk 块，并将分配好的 chunk 块进行连接，添加到自由链表当中
    void *_S_refill(size_t __n) {
        // 一次性分配 20 个内存 chunk 块
        int __nobjs = 20;
        char *__chunk = _S_chunk_alloc(__n, __nobjs);
        _Obj *volatile *__my_free_list;
        _Obj *__result;
        _Obj *__current_obj;
        _Obj *__next_obj;
        int __i;

        if (1 == __nobjs) {
            return (__chunk);
        }

        // 获取对应大小的自由链表
        __my_free_list = _S_free_list + _S_freelist_index(__n);

        // 将新分配的内存 chunk 块添加到对应的自由链表中
        __result = (_Obj *) __chunk;
        *__my_free_list = __next_obj = (_Obj *) (__chunk + __n);
        for (__i = 1;; __i++) {
            __current_obj = __next_obj;
            __next_obj = (_Obj *) ((char *) __next_obj + __n);
            if (__nobjs - 1 == __i) {
                __current_obj->_M_free_list_link = nullptr;
                break;
            } else {
                __current_obj->_M_free_list_link = __next_obj;
            }
        }
        return (__result);
    }

    // 分配相应字节大小的内存 chunk 块
    char *_S_chunk_alloc(size_t __size, int &__nobjs) {
        char *__result;
        size_t __total_bytes = __size * __nobjs;    // 计算需要分配的总字节数
        size_t __bytes_left = _S_end_free - _S_start_free;    // 获取内存池剩余空间

        // 第一种情况：内存池剩余空间完全满足需求
        if (__bytes_left >= __total_bytes) {
            __result = _S_start_free;
            _S_start_free += __total_bytes;
            return (__result);
        }
            // 第二种情况：内存池剩余空间不能满足全部需求，但至少能分配一个以上的内存 chunk 块
        else if (__bytes_left >= __size) {
            __nobjs = (int) (__bytes_left / __size);
            __total_bytes = __size * __nobjs;
            __result = _S_start_free;
            _S_start_free += __total_bytes;
            return (__result);
        }
            // 第三种情况：内存池剩余空间不足一个内存 chunk 块大小
        else {
            // 计算需要申请的内存总量：2倍需求 + 附加量（堆大小的1/16并向上对齐）
            size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4);

            // 尝试利用内存池的剩余碎片
            if (__bytes_left > 0) {
                // 获取对应大小的自由链表
                _Obj *volatile *__my_free_list = _S_free_list + _S_freelist_index(__bytes_left);
                // 将剩余碎片插入自由链表头部（头插法）
                ((_Obj *) _S_start_free)->_M_free_list_link = *__my_free_list;
                *__my_free_list = (_Obj *) _S_start_free;
            }

            // 申请新的内存块到内存池
            _S_start_free = (char *) malloc(__bytes_to_get);

            //  新的内存块申请失败处理
            if (nullptr == _S_start_free) {
                size_t __i;
                _Obj *volatile *__my_free_list;
                _Obj *__p;

                // 尝试从更大的自由链表中查找可用内存块
                // 注意：不尝试更小的请求，因为在多处理器环境中容易导致问题
                for (__i = __size; __i <= (size_t) _MAX_BYTES; __i += (size_t) _ALIGN) {
                    // 获取对应大小的自由链表
                    __my_free_list = _S_free_list + _S_freelist_index(__i);
                    __p = *__my_free_list;
                    // 找到可用内存块
                    if (nullptr != __p) {
                        *__my_free_list = __p->_M_free_list_link;
                        _S_start_free = (char *) __p;
                        _S_end_free = _S_start_free + __i;
                        return (_S_chunk_alloc(__size, __nobjs));
                        // 注意：任何剩余碎片最终会被加入合适的自由链表
                    }
                }

                // 所有自由链表都无可用内存时的最后处理手段
                _S_end_free = nullptr;    // 异常安全处理
                _S_start_free = (char *) malloc_alloc::allocate(__bytes_to_get);    // 使用备用分配策略（可能抛出异常或终止程序）
                // 此处假设分配操作总会成功（要么抛出异常，要么解决问题）
            }

            // 更新内存池管理参数
            _S_heap_size += __bytes_to_get;    // 累计分配的内存总量
            _S_end_free = _S_start_free + __bytes_to_get;    // 设置新的内存池结束位置

            // 递归调用自身处理内存分配请求（此时内存池已有新申请的内存空间）
            return (_S_chunk_alloc(__size, __nobjs));
        }
    }

};

// 初始化类静态成员变量
template<typename T>
char *__default_alloc_template<T>::_S_start_free = nullptr;

template<typename T>
char *__default_alloc_template<T>::_S_end_free = nullptr;

template<typename T>
size_t __default_alloc_template<T>::_S_heap_size = 0;

template<typename T>
std::mutex __default_alloc_template<T>::_S_free_list_mtx[_NFREELISTS];

template<typename T>
typename __default_alloc_template<T>::_Obj *volatile __default_alloc_template<T>::_S_free_list[_NFREELISTS] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
