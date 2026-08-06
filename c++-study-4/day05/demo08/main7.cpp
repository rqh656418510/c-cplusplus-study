/**
 * async、future、packaged_task 使用
 *
 * (g) - `std::packaged_task` 作为可调用对象直接调用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;

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

    // 获取执行结果，特别注意：get_future() 必须在 packaged_task 执行前调用
    std::future<int> result = task.get_future();

    // 直接调用 packaged_task，在当前线程执行（相当于普通函数调用），不会创建子线程，参数是可调用对象的参数
    task(5000);

    // 获取任务执行结果
    const int num = result.get();

    std::cout << "result = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}