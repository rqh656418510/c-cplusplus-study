/**
 * future 其他成员函数、shared_future、ato 使用
 *
 * （a) std::future::wait_for() 的使用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int process(int milliseconds) {
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
    // 启动一个子线程，第二个参数是线程函数的参数
    std::future<int> result = std::async(std::launch::async, process, 5000);
    std::cout << "continue ..." << std::endl;

    // 等待指定时间
    std::future_status status =  result.wait_for(std::chrono::seconds(2));

    // 判断 Future 的状态（任务执行状态）
    if (status == std::future_status::timeout) {
        std::cout << "future timeout" << std::endl;
    }
    else if (status == std::future_status::ready) {
        std::cout << "future ready" << std::endl;
    }else if (status == std::future_status::deferred) {
        std::cout << "future deferred" << std::endl;
    } else {
        std::cout << "future unknow status" << std::endl;
    }

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;
    return 0;
}