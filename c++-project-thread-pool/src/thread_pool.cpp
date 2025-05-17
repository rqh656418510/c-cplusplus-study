
#include<iostream>
#include<functional>
#include<thread>
#include<memory>
#include<mutex>
#include"thread_pool.h"

////////////////////////////////////////// 线程池类 ////////////////////////////////////////////

// 线程池构造
ThreadPool::ThreadPool() {
	initThreadSize_ = INIT_THREAD_SIZE;
	taskSize_ = 0;
	taskQueMaxThreshHold_ = TASK_MAX_THRESHHOLD;
	poolMode_ = PoolMode::MODE_FIXED;
}

// 线程池析构
ThreadPool::~ThreadPool() {

}

// 设置线程池的工作模式
void ThreadPool::setMode(PoolMode mode) {
	poolMode_ = mode;
}

// 设置任务队列的最大容量
void ThreadPool::setTaskQueMaxThreshHold(size_t size) {
	taskQueMaxThreshHold_ = size;
}

// 启动线程池
void ThreadPool::start(int initThreadSize) {
	// 记录初始的线程数量
	initThreadSize_ = initThreadSize;

	// 创建初始线程
	for (int i = 0; i < initThreadSize_; ++i) {
		// 创建线程对象，并将线程处理函数传递给线程对象的构造函数
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this));
		// 将线程对象放入线程列表中
		threads_.emplace_back(std::move(thread));
	}

	// 启动初始线程
	for (int i = 0; i < initThreadSize_; ++i) {
		threads_[i]->start();
	}
}

// 线程处理函数（负责执行任务）
void ThreadPool::threadHandler() {
	// 死循环
	for (;;) {
		// 获取互斥锁
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		std::cout << "thread " << std::this_thread::get_id() << " 等待获取任务..." << std::endl;

		// 等待任务队列不为空
		notEmpty_.wait(lock, [this]() { return taskQueue_.size() > 0; });

		// 从任务队列中获取需要执行的任务
		std::shared_ptr<Task> task = taskQueue_.front();

		// 将任务从任务队列中移除
		taskQueue_.pop();
		taskSize_--;

		std::cout << "thread " << std::this_thread::get_id() << " 成功获取任务..." << std::endl;

		// 如果获取了任务之后，任务队列依旧不为空，则继续通知其他线程执行任务
		if (taskQueue_.size() > 0) {
			notEmpty_.notify_all();
		}

		// 因为刚获取了任务，任务队列肯定有空余位置（不满），通知用户提交任务到线程池
		notFull_.notify_all();

		// 释放互斥锁（在当前线程执行任务之前）
		lock.unlock();

		// 当前线程负责执行任务
		if (task != nullptr) {
			task->run();
		}
	}
}

// 提交任务给线程池
void ThreadPool::submitTask(std::shared_ptr<Task> task) {
	// 获取互斥锁
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// 等待任务队列有空余位置（不满）
	bool result = notFull_.wait_for(lock, std::chrono::seconds(1), [this]() { return taskQueue_.size() < taskQueMaxThreshHold_; });
	if (!result) {
		std::cerr << "task queue is full, submit task failed.";
		return;
	}

	// 如果任务队列有空余位置（不满），则将任务放入任务队列中
	taskQueue_.emplace(task);
	taskSize_++;

	// 因为刚放入了新任务，任务队列肯定不为空，通知线程池分配线程去执行任务
	notEmpty_.notify_all();
}


////////////////////////////////////////// 线程类 /////////////////////////////////////////////


// 线程构造
Thread::Thread(ThreadHandler handler) : threadHandler_(handler) {

}

// 线程析构
Thread::~Thread() {

}

// 启动线程
void Thread::start() {
	// 创建一个线程，并执行线程处理函数
	std::thread t(threadHandler_);

	// 将子线程设置为分离线程
	t.detach();
}
