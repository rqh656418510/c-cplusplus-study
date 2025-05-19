#include<iostream>
#include<vector>
#include<thread>
#include "thread_pool.h"

// 类型重定义
using ULong = unsigned long long;

// 自定义任务类（模拟并行计算）
class CalculateTask : public Task {

public:

    CalculateTask(ULong begin, ULong end) : begin_(begin), end_(end) {

    }

    virtual Any run() override {
        std::cout << "execute task by thread " << std::this_thread::get_id() << std::endl;

        // 当前线程执行计算
        ULong sum = 0;
        for (ULong i = begin_; i <= end_; ++i) {
            sum += i;
        }

        // 模拟任务执行耗时
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // 返回当前线程的计算结果
        return Any(sum);
    }

private:
    ULong begin_;    // 开始计算的位置
    ULong end_;      // 结束计算的位置
};

int main() {
    // 线程池的工作模式
    int poolMode = 0;

    while (true) {
        // 获取用户输入
        std::cout << "请选择线程池的工作模式，0 - Fixed，1 - Cached" << std::endl;
        std::cin >> poolMode;

        // 判断是否为非法输入
        if (std::cin.fail()) {
            // 清除错误标志位
            std::cin.clear();
            // 丢弃错误输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请重新输入一个合法的数字！\n" << std::endl;
        }
        else {
            // 清空输入缓冲区
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    // 局部作用域开始
    {
        // 创建线程池
        ThreadPool pool;

        // 设置线程池的工作模式
        if (poolMode == 0) {
            // Fixed模式（固定大小线程池）
            pool.setMode(PoolMode::MODE_FIXED);
        }
        else {
            // Cached模式（缓存线程池）
            pool.setMode(PoolMode::MODE_CACHED);

            // 设置线程池Cached模式的最大线程数量
            pool.setThreadSizeMaxThreshHold(8);
        }

        // 启动线程池（指定初始的线程数量）
        pool.start(4);

        std::vector<std::shared_ptr<Result>> results;
        ULong begin = 0;
        ULong end = 0;
        ULong step = 100000;

        // 提交多个任务
        for (int i = 0; i < 10; i++) {

            // 计算区间
            begin = end + 1;
            end = begin + step - 1;

            // 创建任务
            std::shared_ptr<Task> task = std::make_shared<CalculateTask>(begin, end);

            // 提交任务
            std::shared_ptr<Result> result = pool.submitTask(task);

            // 存储任务执行结果
            if (result->isValid()) {
                results.emplace_back(result);
            }
        }

        // 统计任务执行结果
        ULong sum = 0;
        for (int i = 0; i < results.size(); i++) {
            // 阻塞等待任务执行完成，并获取任务执行结果
            ULong result = results[i]->get().cast<ULong>();
            sum += result;
        }

        // 输出并行计算结果
        std::cout << "==> 计算结果：1 + 2 + ... + " << end << " = " << sum << std::endl;

    } // 局部作用域结束，线程池自动析构，回收线程池中的所有线程

    // 阻塞主线程，直到用户按下任意键
    char c = getchar();

    return 0;
}
