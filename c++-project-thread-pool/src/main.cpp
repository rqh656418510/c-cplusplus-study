#include<iostream>
#include "thread_pool.h"

// 自定义任务类
class CustomTask : public Task {

    virtual void run() override {
        std::cout << "execute task by thread " << std::this_thread::get_id() << std::endl;

		// 模拟任务执行耗时
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 5 + 1));
    }

};

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 创建线程池
    ThreadPool pool;

    // 启动线程池
    pool.start();

    for (int i = 0; i < 10; i++) {
		// 创建任务
        std::shared_ptr<Task> task = std::make_shared<CustomTask>();
        // 提交任务
        pool.submitTask(task);
    }

    // 主线程等待一段时间
	std::this_thread::sleep_for(std::chrono::seconds(60));

    return 0;
}
