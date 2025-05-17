#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<iostream>
#include<functional>
#include<vector>
#include<queue>
#include<memory>
#include<atomic>
#include<mutex>
#include<condition_variable>

// 线程池支持的模式
enum class PoolMode {
	MODE_FIXED,	// 固定大小线程池
	MODE_CACHED	// 缓存线程池
};

// 任务抽象类
class Task {

public:
	// 纯虚函数，实现自定义任务的处理
	virtual void run() = 0;
};

// 线程类
class Thread {

public:
	// 线程处理函数对象的类型
	using ThreadHandler = std::function<void()>;

	// 线程构造
	Thread(ThreadHandler handler);

	// 线程析构
	~Thread();

	// 启动线程
	void start();

private:
	ThreadHandler threadHandler_;	// 线程处理函数
};

// 线程池类
class ThreadPool {

public:
	// 线程池构造
	ThreadPool();

	// 线程池析构
	~ThreadPool();

	// 设置线程池的工作模式
	void setMode(PoolMode mode);

	// 设置任务队列的最大容量
	void setTaskQueMaxThreshHold(size_t size);

	// 启动线程池
	void start(int initThreadSize = 4);

	// 提交任务给线程池
	void submitTask(std::shared_ptr<Task> task);

	// 禁止拷贝构造
	ThreadPool(const ThreadPool&) = delete;

	// 禁止赋值
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// 线程处理函数（负责执行任务）
	void threadHandler();

private:
	PoolMode poolMode_;									// 线程池的模式
	std::vector<std::unique_ptr<Thread>> threads_;		// 线程列表
	size_t initThreadSize_;								// 初始的线程数量

	std::queue<std::shared_ptr<Task>> taskQueue_;		// 任务队列
	std::atomic_uint taskSize_;							// 任务队列的任务数量
	size_t taskQueMaxThreshHold_;						// 任务队列的最大容量

	std::mutex taskQueMtx_;								// 任务队列操作的互斥锁
	std::condition_variable notFull_;					// 表示任务队列不满，用于通知用户线程提交任务
	std::condition_variable notEmpty_;					// 表示任务队列不空，用于通知线程池执行任务
};

#endif