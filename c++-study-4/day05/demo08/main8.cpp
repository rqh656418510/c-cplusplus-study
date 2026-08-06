/**
 * async、future、packaged_task 使用
 *
 * (h) - `std::packaged_task` + `std::vector` 容器的使用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

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

    // 创建容器
    std::vector<std::packaged_task<int(int)>> tasks;

    // 将 packaged_task 放入容器
    tasks.push_back(std::move(task));

    // 从容器获取 packaged_task
    const auto iter = tasks.begin();
    std::packaged_task<int(int)> task2 = std::move(*iter);

    // 从容器移除 packaged_task，后续不能再使用 iter，否则会出现未定义行为
    tasks.erase(iter);

    // 获取执行结果，特别注意：get_future() 必须在 packaged_task 执行前调用
    std::future<int> result = task2.get_future();

    // 直接调用 packaged_task，在当前线程执行（相当于普通函数调用），不会创建子线程，参数是可调用对象的参数
    task2(5000);

    // 获取任务执行结果
    const int num = result.get();
    std::cout << "result = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;
    return 0;
}