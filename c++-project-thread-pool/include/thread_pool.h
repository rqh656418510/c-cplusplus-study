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
#include<stdexcept>
#include<unordered_map>

// 初始的线程数量
const int INIT_THREAD_SIZE = 4;

// 任务队列的最大任务数量
const int TASK_MAX_THRESHHOLD = 1024;

// 线程池Cached模式的最大线程数量
const int THREAD_SIZE_MAX_THRESHHOLD = 200;

// 线程允许的最大空闲时间（单位秒）
const int THREAD_MAX_IDLE_TIME = 10;

// 线程池支持的模式
enum class PoolMode {
	MODE_FIXED,	// 固定大小线程池
	MODE_CACHED	// 缓存线程池
};

// Any 类型（可以接收任意数据类型）
class Any {

public:
	// 构造函数
	Any() = default;

	// 析构函数
	~Any() = default;

	// 禁止带左值的拷贝构造函数
	Any(const Any&) = delete;

	// 禁止带左值的赋值运算符
	Any& operator=(const Any&) = delete;

	// 带右值的拷贝构造函数（移动拷贝构造）
	Any(Any&&) = default;

	// 带右值的赋值运算符（移动赋值运算符）
	Any& operator=(Any&&) = default;

	// 构造函数（让 Any 类型可以接收任意数据类型）
	template<typename T>
	Any(T data) : base_(std::make_unique<Derive<T>>(data)) {

	}

	// 类型转换（将 Any 类型存储的数据类型提取出来）
	template<typename T>
	T cast() {
		// 将基类指针转换为派生类指针（向下转换）
		Derive<T>* p = dynamic_cast<Derive<T>*>(base_.get());
		if (p == nullptr) {
			throw std::runtime_error("type is unmatch!");
		}
		// 返回真实的数据类型
		return p->getData();
	}

private:
	// 基类类型
	class Base {

	public:
		// 虚析构函数
		virtual ~Base() = default;
	};

	// 派生类类型
	template<typename T>
	class Derive : public Base {

	public:
		// 构造函数
		Derive(T data) : data_(data) {

		}
		
		// 析构函数
		~Derive() {

		}

		T getData() const {
			return data_;
		}

	private:
		T data_;
	};

private:
	std::unique_ptr<Base> base_;	// 基类指针

};

// 信号量类
class Semaphore {

public:
	// 构造函数
	Semaphore(int limit = 0) : limit_(limit) {

	}

	// 析构函数
	~Semaphore() = default;

	// 获取一个信号量资源
	void wait() {
		// 获取互斥锁
		std::unique_lock<std::mutex> lock(mtx_);

		// 等待信号量资源
		cond_.wait(lock, [this]() { return limit_ > 0; });

		// 更改资源计数
		limit_--;
	}

	// 增加一个信号量资源
	void post() {
		// 获取互斥锁
		std::unique_lock<std::mutex> lock(mtx_);

		// 更改资源计数
		limit_++;

		// 通知其他线程获取信号量资源
		cond_.notify_all();
	}

private:
	int limit_;						// 资源计数
	std::mutex mtx_;				// 互斥锁
	std::condition_variable cond_;  // 条件变量
};

// 任务执行结果类的前置声明
class Result;

// 任务抽象类
class Task {

public:
	// 构造函数
	Task();

	// 析构函数
	~Task() = default;

	// 纯虚函数，实现用户自定义的任务处理逻辑
	virtual Any run() = 0;

	// 执行任务
	void exec();

	// 设置任务执行结果
	void setResult(Result* p);

private:
	Result* result_;	// 任务执行结果（使用裸指针，避免智能指针循环引用问题）
};

// 任务执行结果类
class Result {

public:
	// 构造函数
	Result(std::shared_ptr<Task> task, bool isValid = true);

	// 析构函数
	~Result() = default;

	// 获取任务执行结果
	Any get();

	// 设置任务执行结果
	void setVal(Any data);

	// 获取任务执行结果是否有效
	bool isValid() const;

private:
	Any data_;						// 存储任务执行的结果
	Semaphore sem_;					// 线程通信的信号量
	std::shared_ptr<Task> task_;	// 关联对应的任务
	std::atomic_bool isValid_;		// 任务执行结果是否有效
};

// 线程类
class Thread {

public:
	// 线程处理函数对象的类型
	using ThreadHandler = std::function<void(int)>;

	// 线程构造
	Thread(ThreadHandler handler);

	// 线程析构
	~Thread();

	// 启动线程
	void start();

	// 获取线程ID
	int getId() const;

private:
	int threadId_;					// 线程ID
	static int generateId_;			// 用于辅助生成全局唯一的线程ID
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

	// 设置线程池Cached模式的最大线程数量
	void setThreadSizeMaxThreshHold(int threshhold);

	// 设置任务队列的最大任务数量
	void setTaskQueMaxThreshHold(size_t threshhold);

	// 启动线程池
	void start(int initThreadSize = INIT_THREAD_SIZE);

	// 提交任务给线程池
	std::shared_ptr<Result> submitTask(std::shared_ptr<Task> task);

	// 禁止拷贝构造
	ThreadPool(const ThreadPool&) = delete;

	// 禁止赋值
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// 线程处理函数（负责执行任务）
	void threadHandler(int threadId);

	// 检查线程池的运行状态
	bool checkRunningState() const;

private:
	std::unordered_map<int, std::unique_ptr<Thread>> threads_;		// 线程集合
	PoolMode poolMode_;												// 线程池的模式
	std::atomic_bool isPoolRuning_;									// 表示线程池是否正在运行
	

	size_t initThreadSize_;											// 初始的线程数量
	std::atomic_int idleThreadSize_;								// 空闲线程的数量
	std::atomic_int curThreadSize_;									// 当前线程池的线程数量
	int threadSizeMaxThreshHold_;									// 线程池Cached模式的最大线程数量

	std::queue<std::shared_ptr<Task>> taskQueue_;					// 任务队列
	std::atomic_uint taskSize_;										// 当前任务队列的任务数量
	size_t taskQueMaxThreshHold_;									// 任务队列的最大任务数量

	std::mutex taskQueMtx_;											// 任务队列操作的互斥锁
	std::condition_variable notFull_;								// 表示任务队列不满，用于通知用户线程提交任务
	std::condition_variable notEmpty_;								// 表示任务队列不空，用于通知线程池执行任务
};

#endif