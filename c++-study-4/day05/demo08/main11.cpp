/**
 * async、future、packaged_task 使用
 *
 * std::promise 的使用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void process(std::promise<int>& result, int milliseconds) {
    std::cout << "process() start, current thread id " << std::this_thread::get_id() << std::endl;

    // 模拟业务处理耗时
    const std::chrono::milliseconds ms(milliseconds);
    std::this_thread::sleep_for(ms);

    std::cout << "process() end, current thread id " << std::this_thread::get_id() << std::endl;

    // 设置业务处理结果
    result.set_value(5);
}

void process2(std::future<int> result) {
    std::cout << "process2() start, current thread id " << std::this_thread::get_id() << std::endl;

    // 阻塞等待任务执行结果
    const int num = result.get();
    std::cout << "result = " << num << std::endl;

    std::cout << "process2() end, current thread id " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;

    // 创建 Promise 对象
    std::promise<int> mpro;

    // 获取执行结果，特别注意：get_future() 应该在子线程执行前调用
    std::future<int> result = mpro.get_future();

    // 创建子线程 1，第一个参数是线程函数，第二个参数是 Promise 对象的引用，第三个参数毫秒数
    std::thread t1(process, std::ref(mpro), 5000);

    // 创建子线程 2，第一个参数是线程函数，第二个参数是 Future 对象
    // future 不支持拷贝，通过移动转移所有权
    std::thread t2(process2, std::move(result));

    // 阻塞等待子线程执行完成
    t1.join();
    t2.join();

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;
    return 0;
}