/**
* future 其他成员函数、shared_future、ato 使用
 *
 * （b) std::shared_future 的使用
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

void process2(const std::shared_future<int> &result) {
    std::cout << "process2() start, current thread id " << std::this_thread::get_id() << std::endl;

    // 获取其他线程的执行结果
    std::cout << "result = " << result.get() << std::endl;

    std::cout << "process2() end, current thread id " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "main() run, thread id " << std::this_thread::get_id() << std::endl;

    // 创建 packaged_task，参数是可调用对象（比如普通函数）
    std::packaged_task<int(int)> task(process);

    // 获取子线程的执行结果，特别注意：get_future() 必须在 packaged_task 执行前调用
    std::future<int> result = task.get_future();

    // 将 future 转换为 shared_future
    // std::shared_future<int> result2(std::move(result));
    std::shared_future<int> result2(result.share());

    // 创建子线程 1（第二个参数是线程函数的参数），子线程会直接执行
    std::thread t1(std::ref(task), 5000);

    // 创建子线程 2（第二个参数是线程函数的参数），子线程会直接执行
    std::thread t2(process2, std::ref(result2));

    // 等待子线程 1 执行完成
    t1.join();

    // 等待子线程 2 执行完成
    t2.join();

    // 获取其他线程的执行结果
    const int num = result2.get();
    std::cout << "result = " << num << std::endl;

    std::cout << "main() end, thread id " << std::this_thread::get_id() << std::endl;

    return 0;
}