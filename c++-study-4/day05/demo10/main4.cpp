/**
 * std::atomic续谈、std::async深入谈
 *
 * （d) std::async 深入使用
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
    std::future<int> result = std::async(std::launch::async | std::launch::deferred, process, 5000);

    std::cout << "continue ..." << std::endl;

    // 上面的两种启动策略任意选择一种（选择的结果是不确定的，由标准库实现自行选择）
    const int num = result.get();
    std::cout << "num = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}
