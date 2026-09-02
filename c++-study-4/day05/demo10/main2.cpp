/**
 * std::atomic续谈、std::async深入谈
 *
 * （b) std::async 深入使用
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

    // 第一个参数是启动策略，第二个参数是线程函数，第三个参数是线程函数的参数
    std::future<int> result = std::async(std::launch::deferred, process, 5000);

    std::cout << "continue ..." << std::endl;

    // 使用 std::launch::deferred 执行策略后，不会创建子线程，当 get() 被调用后才会在当前主线程（非子线程）开始执行任务
    // 如果 get() 或者 wait() 不被调用，那么任务永远不会执行
    const int num = result.get();
    std::cout << "num = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}
