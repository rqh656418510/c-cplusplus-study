/**
 * std::atomic续谈、std::async深入谈
 *
 * （c) std::async 深入使用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int process(const int milliseconds) {
    std::cout << "process() start, current thread id " << std::this_thread::get_id() << std::endl;

    // 模拟业务处理耗时
    const std::chrono::milliseconds ms(milliseconds);
    std::this_thread::sleep_for(ms);

    std::cout << "process() end, current thread id " << std::this_thread::get_id() << std::endl;

    // 返回业务处理结果
    return 5;
}

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;

    // 第一个参数是执行策略，第二个参数是线程函数，第三个参数是线程函数的参数
    std::future<int> result = std::async(std::launch::async, process, 5000);

    std::cout << "continue ..." << std::endl;

    // 使用 std::launch::async 执行策略后，会立即创建子线程执行任务，主线程调用 get() 后会阻塞等待任务执行完成并获取执行结果
    // 这里即使不手动调用 get() 或者 wait()，主线程也会等待子线程执行完成后再结束
    const int num = result.get();
    std::cout << "num = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}
