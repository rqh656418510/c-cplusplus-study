
#include<iostream>
#include<functional>
#include<thread>
#include<memory>
#include<mutex>
#include"thread_pool.h"

////////////////////////////////////////// 线程池类 ////////////////////////////////////////////

// 线程池构造
ThreadPool::ThreadPool() {
	idleThreadSize_ = 0;
	curThreadSize_ = INIT_THREAD_SIZE;
	initThreadSize_ = INIT_THREAD_SIZE;
	threadSizeMaxThreshHold_ = THREAD_SIZE_MAX_THRESHHOLD;
	taskSize_ = 0;
	taskQueMaxThreshHold_ = TASK_MAX_THRESHHOLD;
	poolMode_ = PoolMode::MODE_FIXED;
	isPoolRuning_ = false;
	
}

// 线程池析构
ThreadPool::~ThreadPool() {
	// 设置线程池的运行状态
	isPoolRuning_ = false;

	// 唤醒所有正在等待获取任务的线程
	notEmpty_.notify_all();

	// 获取互斥锁
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// 等待线程池里的所有线程回收完成
	allExit_.wait(lock, [this]() { return threads_.size() == 0; });
}

// 设置线程池的工作模式
void ThreadPool::setMode(PoolMode mode) {
	if (!checkRunningState()) {
		poolMode_ = mode;
	}
}

// 设置线程池Cached模式的最大线程数量
void ThreadPool::setThreadSizeMaxThreshHold(int threshhold) {
	if (PoolMode::MODE_CACHED == poolMode_ && !checkRunningState()) {
		threadSizeMaxThreshHold_ = threshhold;
	}
}

// 设置任务队列的最大任务数量
void ThreadPool::setTaskQueMaxThreshHold(size_t threshhold) {
	if (!checkRunningState()) {
		taskQueMaxThreshHold_ = threshhold;
	}
}

// 检查线程池的运行状态
bool ThreadPool::checkRunningState() const{
	return isPoolRuning_;
}

// 启动线程池
void ThreadPool::start(int initThreadSize) {
	// 设置线程池的运行状态
	isPoolRuning_ = true;

	// 记录初始的线程数量
	initThreadSize_ = initThreadSize;

	// 创建初始的线程
	for (int i = 0; i < initThreadSize_; i++) {
		// 创建线程对象，并将线程处理函数传递给线程对象的构造函数
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
		// 将线程对象放入线程集合中
		threads_.emplace(thread->getId(), std::move(thread));
	}

	// 启动初始的线程
	for (int i = 0; i < initThreadSize_; i++) {
		threads_[i]->start();	// 启动一个线程去执行线程处理函数
		idleThreadSize_++;		// 记录初始空闲线程的数量
	}
}

// 线程处理函数（负责执行任务）
void ThreadPool::threadHandler(int threadId) {
	// 记录线程首次运行的时间
	auto lastTime = std::chrono::high_resolution_clock().now();

	// 线程一直循环运行
	while (checkRunningState()) {
		// 获取互斥锁
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		std::cout << "thread " << std::this_thread::get_id() << " 等待获取任务..." << std::endl;
		
		// 使用while循环避免虚假唤醒
		while (taskQueue_.size() == 0) {
			// 线程池Cached模式的处理
			if (PoolMode::MODE_CACHED == poolMode_) {
				// 等待一段时间
				std::cv_status waitResult = notEmpty_.wait_for(lock, std::chrono::seconds(1));
				// 需要区分超时返回，还是线程正常被唤醒返回
				if (std::cv_status::timeout == waitResult) {
					auto nowTime = std::chrono::high_resolution_clock().now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(nowTime - lastTime);
					// 当线程的空闲时间超过最大阀值，且当前线程池的线程数量大于初始线程数量，则开始回收线程池中的空闲线程
					if (duration.count() > THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_) {
						// 从线程集合中删除当前线程
						threads_.erase(threadId);
						// 更新空闲线程的数量
						idleThreadSize_--;
						// 更新当前线程池的线程数量
						curThreadSize_--;
						// 打印日志信息
						std::cout << "thread " << threadId << " exited." << std::endl;
						return;
					}
				}
			}
			// 线程池Fixed模式的处理
			else {
				// 等待任务队列不为空
				notEmpty_.wait(lock);
			}

			// 如果线程池要结束运行，则回收线程资源
			if (!checkRunningState()) {
				// 从线程集合中删除当前线程
				threads_.erase(threadId);
				// 唤醒等待线程池回收完毕的线程
				allExit_.notify_all();
				// 打印日志信息
				std::cout << "thread pool destroy, thread " << threadId << " exited." << std::endl;
				return;
			}
		}

		// 空闲线程数量减一（线程执行任务之前）
		idleThreadSize_--;

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
			task->exec();
		}

		// 空闲线程数量加一（线程执行完任务之后）
		idleThreadSize_++;

		// 更新线程最后执行完任务的时间
		lastTime = std::chrono::high_resolution_clock().now();
	}

	// 由于线程池要结束运行，因此从线程集合中删除当前线程
	threads_.erase(threadId);

	// 唤醒等待线程池回收完毕的线程
	allExit_.notify_all();

	// 打印日志信息
	std::cout << "thread pool destroy_xxx, thread " << threadId << " exited." << std::endl;
}

// 提交任务给线程池
std::shared_ptr<Result> ThreadPool::submitTask(std::shared_ptr<Task> task) {
	// 获取互斥锁
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// 等待任务队列有空余位置（不满）
	bool waitResult = notFull_.wait_for(lock, std::chrono::seconds(1), [this]() { return taskQueue_.size() < taskQueMaxThreshHold_; });
	if (!waitResult) {
		std::cerr << "task queue is full, submit task failed.";
		return std::make_shared<Result>(task, false);
	}

	// 如果任务队列有空余位置（不满），则将任务放入任务队列中
	taskQueue_.emplace(task);
	taskSize_++;

	// 因为刚放入了新任务，任务队列肯定不为空，通知线程池中的线程去执行任务
	notEmpty_.notify_all();

	// 线程池Cached模式的处理，根据任务数量动态增加线程池的线程数量
	if (PoolMode::MODE_CACHED == poolMode_ && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeMaxThreshHold_) {
		// 打印日志信息
		std::cout << "expand and create new thread." << std::endl;
		// 创建新线程对象，并将线程处理函数传递给线程对象的构造函数
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
		// 获取线程ID（必须在线程放入线程集合之前获取一次线程ID，否则后续将可能获取到空值）
		int threadId = thread->getId();
		// 将新线程对象放入线程集合中
		threads_.emplace(threadId, std::move(thread));
		// 启动新线程
		threads_[threadId]->start();
		// 更新空闲线程的数量
		idleThreadSize_++;
		// 更新当前线程池的线程数量
		curThreadSize_++;
	}

	// 返回任务执行结果
	return std::make_shared<Result>(task);
}


////////////////////////////////////////// 线程类 /////////////////////////////////////////////


// 线程构造
Thread::Thread(ThreadHandler handler) : threadHandler_(handler),threadId_(generateId_++) {

}

// 线程析构
Thread::~Thread() {

}

// 启动线程
void Thread::start() {
	// 创建一个线程，并执行线程处理函数
	std::thread t(threadHandler_, threadId_);

	// 将子线程设置为分离线程
	t.detach();
}


// 获取线程ID
int Thread::getId() const {
	return threadId_;
}

// 用于辅助生成全局唯一的线程ID
int Thread::generateId_ = 0;


////////////////////////////////////////// 任务抽象类 /////////////////////////////////////////////


// 构造函数
Task::Task() : result_(nullptr) {

}

// 执行任务
void Task::exec() {
	// 执行任务处理逻辑（发生多态调用）
	Any data = run();

	// 设置任务执行结果
	if (result_ != nullptr) {
		result_->setVal(std::move(data));
	}
}

// 设置任务执行结果
void Task::setResult(Result * p) {
	result_ = p;
}


////////////////////////////////////////// 任务结果类 /////////////////////////////////////////////


// 构造函数
Result::Result(std::shared_ptr<Task> task, bool isValid) : task_(task), isValid_(isValid) {
	// 关联任务和任务执行结果
	task->setResult(this);
}

// 获取任务执行结果
Any Result::get() {
	// 如果任务执行结果无效，直接返回
	if (!isValid_) {
		// TODO 优化代码
		return "";
	}

	// 等待获取一个信号量资源（即让当前线程等待任务执行结果）
	sem_.wait();

	// 返回任务执行结果
	return std::move(data_);
}

// 设置任务执行结果
void Result::setVal(Any data) {
	// 存储任务执行结果
	data_ = std::move(data);

	// 增加一个信号量资源（即通知其他线程获取任务执行结果）
	sem_.post();
}

// 获取任务执行结果是否有效
bool Result::isValid() const {
	return isValid_;
}
