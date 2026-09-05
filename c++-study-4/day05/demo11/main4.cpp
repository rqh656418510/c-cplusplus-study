/**
* windows临界区、其他各种mutex互斥量
 *
 * （d) std::timed_mutex 的使用
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class MyClass {

public:
    void process() {
        // 尝试获取锁，最多等待 3 秒
        if (m_mutex.try_lock_for(std::chrono::seconds(3))) {
            std::cout << "成功获取锁, 线程 ID 是 " << std::this_thread::get_id() << std::endl;

            // 模拟业务处理耗时
            std::this_thread::sleep_for(std::chrono::seconds(5));

            // 解锁
            m_mutex.unlock();
        }
        else {
            std::cout << "获取锁超时, 线程 ID 是 " << std::this_thread::get_id() << std::endl;
        }
    }
private:
    std::timed_mutex m_mutex;  // 带超时功能的互斥锁
};

int main() {
    MyClass obj;

    // 创建并启动线程 1
    std::thread t1(&MyClass::process, &obj);

    // 创建并启动线程 2
    std::thread t2(&MyClass::process, &obj);

    // 等待线程 1 执行完成
    t1.join();

    // 等待线程 2 执行完成
    t2.join();

    return 0;
}