/**
 * async、future、packaged_task 使用
 *
 * (a) `std::async` + 普通函数的使用
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
    std::future<int> result = std::async(process, 5000);
    std::cout << "continue ..." << std::endl;
    // 获取子线程的执行结果（阻塞等待线程执行完成）
    const int num = result.get();
    std::cout << "result = " << num << std::endl;
    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;
    return 0;
}