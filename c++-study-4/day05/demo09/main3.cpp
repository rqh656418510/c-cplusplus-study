/**
* future 其他成员函数、shared_future、ato 使用
 *
 * （c) std::atomic 的使用
 */

#include <iostream>
#include <thread>
#include <atomic>

// 定义全局变量（使用原子类型）
static std::atomic<int> g_count(0);

void process()
{
    for (int i = 0; i < 1000000; ++i)
    {
        g_count++;
    }
}

int main()
{
    // 创建子线程 1
    std::thread t1(process);

    // 创建子线程 2
    std::thread t2(process);

    // 等待子线程 1 执行完成
    t1.join();

    // 等待子线程 2 执行完成
    t2.join();

    // 预期输出结果是：2000000
    std::cout << "count = " << g_count.load() << std::endl;

    return 0;
}