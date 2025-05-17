#include<iostream>
#include "thread_pool.h"

// 自定义任务类（模拟并行计算）
class CalculateTask : public Task {

public:

	CalculateTask(int begin, int end) : begin_(begin), end_(end) {

	}

    virtual Any run() override {
        std::cout << "execute task by thread " << std::this_thread::get_id() << std::endl;

		// 执行计算
        int sum = 0;
        for (int i = begin_; i <= end_; ++i) {
			sum += i;
        }

		// 模拟任务执行耗时
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 5 + 1));

		return Any(sum);
	}

private:
    int begin_;
    int end_;
};

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 创建线程池
    ThreadPool pool;

    // 启动线程池
    pool.start();

    int begin = 0;
	int end = 0;
    int step = 10000;

    // 提交多个任务
    for (int i = 0; i < 10; i++) {

        // 计算区间
		begin = end;
		end = begin + 10000;

		// 创建任务
        std::shared_ptr<Task> task = std::make_shared<CalculateTask>(begin, end);

        // 提交任务
		pool.submitTask(task);
    }

    // 阻塞主线程
	char c = getchar();

    return 0;
}
