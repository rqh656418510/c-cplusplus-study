/**
 * 基于CAS操作的atomic原子类型
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <list>

std::atomic_int _count = 0;
std::atomic_bool _isReady = false;

void taskHandler() {
    while (!_isReady) {
        // 线程出让当前的 CPU 时间片，等待下一次调度的执行
        std::this_thread::yield();
    }

    for (int i = 0; i < 100; i++) {
		_count++;
    }
}

int main() {
    std::list<std::thread> list;

    // 创建多个子线程
    for (int i = 0; i < 10; i++) {
        list.push_back(std::thread(taskHandler));
    }

    // 主线程等待几秒
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _isReady = true;

    // 等待所有子线程执行结束
    for (auto it = list.begin(); it != list.end(); ++it) {
        (*it).join();
    }

    std::cout << "_count = " << _count << std::endl;

    return 0;
}
