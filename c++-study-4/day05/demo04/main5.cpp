/**
 * 互斥量概念、用法、死锁演示及解决详解
 *
 * (e) 解决线程死锁的案例（使用 std::lock() 一次性获取所有锁）
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

class MyClass {
public:
    void func1() {
        std::cout << "thread 1 wait to get locker 1 and locker 2" << std::endl;

        // 一次性锁住两个互斥量
        std::lock(lock1, lock2);

        std::cout << "thread 1 already got locker 1 and locker 2" << std::endl;

        // 使用 std::adopt_lock 表明锁已经持有
        std::lock_guard<std::mutex> g1(lock1, std::adopt_lock);
        std::lock_guard<std::mutex> g2(lock2, std::adopt_lock);

        // 模拟业务执行耗时（临界区代码）
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "thread 1 already released locker 1 and locker 2" << std::endl;

        // std::lock_guard 析构时会自动释放锁
    }

    void func2() {
        std::cout << "thread 2 wait to get locker 1 and locker 2" << std::endl;

        // 一次性锁住两个互斥量（顺序与 func1 不同也没关系）
        std::lock(lock1, lock2);

        std::cout << "thread 2 already got locker 1 and locker 2" << std::endl;

        // 使用 std::adopt_lock 表明锁已经持有
        std::lock_guard<std::mutex> g1(lock1, std::adopt_lock);
        std::lock_guard<std::mutex> g2(lock2, std::adopt_lock);

        // 模拟业务执行耗时（临界区代码）
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "thread 2 already released locker 1 and locker 2" << std::endl;

        // std::lock_guard 析构时会自动释放锁
    }

private:
    std::mutex lock1;  // 锁 1
    std::mutex lock2;  // 锁 2
};

int main() {
    std::cout << "main thread start." << std::endl;

    MyClass mc;

    // 创建并启动线程 1
    std::thread t1(&MyClass::func1, &mc);

    // 创建并启动线程 2
    std::thread t2(&MyClass::func2, &mc);

    // 等待线程 1 执行结束
    t1.join();

    // 等待线程 2 执行结束
    t2.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}