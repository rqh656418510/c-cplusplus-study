/**
 * std::atomic续谈、std::async深入谈
 *
 * （e) 判断 std::async 使用哪种启动策略
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

    // 判断 std::async 使用哪种启动策略
    const std::future_status status = result.wait_for(std::chrono::seconds(0));
    if ( status == std::future_status::deferred ) {
        // 延迟执行策略
        std::cout << "thread deferred" << std::endl;
        const int num = result.get();
        std::cout << "result = " << num << std::endl;
    } else {
        // 异步执行策略
        if (status == std::future_status::ready) {
            // 线程执行完成并返回结果
            std::cout << "thread finish" << std::endl;
            const int num = result.get();
            std::cout << "result = " << num << std::endl;
        }
        else {
            // 线程执行超时
            std::cout << "thread timeout" << std::endl;
            const int num = result.get();
            std::cout << "result = " << num << std::endl;
        }
    }

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}
