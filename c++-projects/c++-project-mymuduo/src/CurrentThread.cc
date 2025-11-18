#include "CurrentThread.h"

#include <sys/syscall.h>
#include <unistd.h>

namespace CurrentThread {

    // 定义线程局部变量（thread-local），用于缓存当前线程的 ID
    __thread int t_cachedTid = 0;

    // 定义缓存当前线程的 ID 的函数
    void cacheTid() {
        if (t_cachedTid == 0) {
            // 通过 Linux 系统调用，获取当前线程的 ID
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }

}  // namespace CurrentThread