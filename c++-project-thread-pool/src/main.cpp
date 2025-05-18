#include<iostream>
#include<vector>
#include "thread_pool.h"

// 类型重定义
using ulong = unsigned long long;

// 自定义任务类（模拟并行计算）
class CalculateTask : public Task {

public:

	CalculateTask(ulong begin, ulong end) : begin_(begin), end_(end) {

	}

    virtual Any run() override {
        std::cout << "execute task by thread " << std::this_thread::get_id() << std::endl;

		// 执行计算
        ulong sum = 0;
        for (ulong i = begin_; i <= end_; ++i) {
			sum += i;
        }

		// 模拟任务执行耗时
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 5 + 1));

		return Any(sum);
	}

private:
    ulong begin_;
    ulong end_;
};

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 创建线程池
    ThreadPool pool;

    // 设置线程池的工作模式
	pool.setMode(PoolMode::MODE_CACHED);

    // 启动线程池
    pool.start();

	std::vector<std::shared_ptr<Result>> results;
    ulong begin = 0;
	ulong end = 0;
	ulong step = 100000;

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
	ulong sum = 0;
    for (int i = 0; i < results.size(); i++) {
		// 阻塞等待任务执行完成，并获取执行结果
		ulong result = results[i]->get().cast<ulong>();
        sum += result;
	}
    
    // 输出并行计算结果
	std::cout << "1 + 2 + ... + " << end << " = " << sum << std::endl;

    // 阻塞主线程
	char c = getchar();

    return 0;
}
