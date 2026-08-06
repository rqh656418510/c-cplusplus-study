/**
* async、future、packaged_task 使用
 *
 * (c) `std::async` + `std::launch::deferred` 的使用
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

class MyClass {
public:
    int process(const int milliseconds) {
        std::cout << "process() start, current thread id " << std::this_thread::get_id() << std::endl;
        // 模拟业务处理耗时
        const std::chrono::milliseconds ms(milliseconds);
        std::this_thread::sleep_for(ms);
        std::cout << "process() end, current thread id " << std::this_thread::get_id() << std::endl;
        // 返回业务处理结果
        return 5;
    }
};

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;
    MyClass mc;
    // 第一个参数是执行策略，第三个参数是对象引用，第四个参数是线程函数的参数
    std::future<int> result = std::async(std::launch::deferred, &MyClass::process, &mc, 5000);
    std::cout << "continue ..." << std::endl;
    // 使用 std::launch::deferred 执行策略后，不会创建子线程，当 get() 被调用后才会在当前主线程（非子线程）开始执行任务
    const int num = result.get();
    std::cout << "result = " << num << std::endl;
    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;
    return 0;
}