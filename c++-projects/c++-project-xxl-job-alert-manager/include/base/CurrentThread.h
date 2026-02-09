#pragma once

namespace CurrentThread {

// 声明线程局部变量（thread-local），用于缓存当前线程的 ID
extern __thread int t_cachedTid;

// 声明缓存当前线程的 ID 的函数
void cacheTid();

// 获取当前线程的 ID
inline int tid() {
    if (__builtin_expect(t_cachedTid == 0, 0)) {
        cacheTid();
    }
    return t_cachedTid;
}

}  // namespace CurrentThread