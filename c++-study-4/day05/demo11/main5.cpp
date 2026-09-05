/**
 * windows临界区、其他各种mutex互斥量
 *
 * （e) std::recursive_timed_mutex 的使用
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

class MyClass {
public:
    void process(int count) {
        // 先创建 unique_lock，但暂时不加锁
        std::unique_lock<std::recursive_timed_mutex> lock(m_mutex, std::defer_lock);

        if (lock.try_lock_for(std::chrono::seconds(3))) {
            std::cout << "成功获取锁, 线程 ID 是 " << std::this_thread::get_id() << ", count = " << count << std::endl;

            // 模拟业务处理耗时
            std::this_thread::sleep_for(std::chrono::seconds(2));

            if (count > 0) {
                // 递归调用，再次获取同一把锁
                process((count - 1));
            }

            // 这里不需要手动调用 unlock()，离开作用域后，unique_lock 析构时会自动释放锁
        } else {
            std::cout << "获取锁超时, 线程 ID 是 " << std::this_thread::get_id() << std::endl;
        }
    }

private:
    std::recursive_timed_mutex m_mutex;  // 支持递归加锁和超时功能的互斥锁
};

int main() {
    MyClass obj;

    obj.process(3);

    return 0;
}