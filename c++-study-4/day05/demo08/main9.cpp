/**
 * async、future、packaged_task 使用
 *
 * (i) - `std::packaged_task` + `std::queue` 实现任务队列（常用于线程池）
 */

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;

    // 创建任务队列
    std::queue<std::packaged_task<int(int)>> tasks;

    // 创建互斥锁，保护任务队列
    std::mutex mutex;

    // 创建 packaged_task，参数是可调用对象（比如 Lambda 表达式）
    std::packaged_task<int(int)> task([](const int milliseconds) -> int {
        std::cout << "process start, current thread id " << std::this_thread::get_id() << std::endl;

        // 模拟业务处理耗时
        const std::chrono::milliseconds ms(milliseconds);
        std::this_thread::sleep_for(ms);

        std::cout << "process end, current thread id " << std::this_thread::get_id() << std::endl;

        // 返回业务处理结果
        return 5;
    });

    // 获取 future，必须在 packaged_task 执行前调用
    std::future<int> result = task.get_future();

    {
        // 加锁，将任务放入任务队列
        std::lock_guard<std::mutex> lock(mutex);

        // 将 packaged_task 放入任务队列
        tasks.push(std::move(task));
    }

    // 创建工作线程，模拟任务消费者
    std::thread worker([&tasks, &mutex]() {
        std::cout << "worker thread start, thread id " << std::this_thread::get_id() << std::endl;

        std::packaged_task<int(int)> current_task;

        {
            // 加锁，从任务队列获取任务
            std::lock_guard<std::mutex> lock(mutex);

            // 判断任务队列是否为空
            if (!tasks.empty()) {
                // 从任务队列获取 packaged_task
                current_task = std::move(tasks.front());

                // 从队列移除 packaged_task
                tasks.pop();
            }
        }

        // 判断是否成功获取任务
        if (current_task.valid()) {
            // 执行 packaged_task，在当前线程执行，不会创建新的线程，参数是可调用对象的参数
            current_task(5000);
        }

        std::cout << "worker thread end, thread id " << std::this_thread::get_id() << std::endl;
    });

    // 等待工作线程执行完成
    worker.join();

    // 获取执行结果
    const int num = result.get();
    std::cout << "result = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}