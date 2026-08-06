/**
 * async、future、packaged_task 使用
 *
 * (e) `std::packaged_task` + 普通函数的使用
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

    // 创建 packaged_task，参数是可调用对象（比如普通函数）
    std::packaged_task<int(int)> task(process);

    // 获取子线程的执行结果，特别注意：get_future() 必须在 packaged_task 执行前调用
    std::future<int> result = task.get_future();

    // 创建子线程（第二个参数是线程函数的参数），子线程会直接执行
    std::thread t1(std::ref(task), 5000);

    // 等待子线程执行完成
    t1.join();

    // 获取执行结果
    const int num = result.get();

    std::cout << "result = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}