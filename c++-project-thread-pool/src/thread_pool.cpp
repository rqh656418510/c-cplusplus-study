
#include<iostream>
#include<functional>
#include<thread>
#include<memory>
#include<mutex>
#include"thread_pool.h"

////////////////////////////////////////// �̳߳��� ////////////////////////////////////////////

// �̳߳ع���
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

// �̳߳�����
ThreadPool::~ThreadPool() {

}

// �����̳߳صĹ���ģʽ
void ThreadPool::setMode(PoolMode mode) {
	if (!checkRunningState()) {
		poolMode_ = mode;
	}
}

// �����̳߳�Cachedģʽ������߳�����
void ThreadPool::setThreadSizeMaxThreshHold(int threshhold) {
	if (PoolMode::MODE_CACHED == poolMode_ && !checkRunningState()) {
		threadSizeMaxThreshHold_ = threshhold;
	}
}

// ����������е������������
void ThreadPool::setTaskQueMaxThreshHold(size_t threshhold) {
	if (!checkRunningState()) {
		taskQueMaxThreshHold_ = threshhold;
	}
}

// ����̳߳ص�����״̬
bool ThreadPool::checkRunningState() const{
	return isPoolRuning_;
}

// �����̳߳�
void ThreadPool::start(int initThreadSize) {
	// �����̳߳ص�����״̬
	isPoolRuning_ = true;

	// ��¼��ʼ���߳�����
	initThreadSize_ = initThreadSize;

	// ������ʼ���߳�
	for (int i = 0; i < initThreadSize_; i++) {
		// �����̶߳��󣬲����̴߳��������ݸ��̶߳���Ĺ��캯��
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
		// ���̶߳�������̼߳�����
		threads_.emplace(thread->getId(), std::move(thread));
	}

	// ������ʼ���߳�
	for (int i = 0; i < initThreadSize_; i++) {
		threads_[i]->start();	// ����һ���߳�ȥִ���̴߳�����
		idleThreadSize_++;		// ��¼��ʼ�����̵߳�����
	}
}

// �̴߳�����������ִ������
void ThreadPool::threadHandler(int threadId) {

	auto lastTime = std::chrono::high_resolution_clock().now();

	// ��ѭ��
	for (;;) {
		// ��ȡ������
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		std::cout << "thread " << std::this_thread::get_id() << " �ȴ���ȡ����..." << std::endl;

		// �̳߳�Cachedģʽ�Ĵ��������̳߳��еĿ����߳�
		if (PoolMode::MODE_CACHED == poolMode_) {
			// ʹ��whileѭ��������ٻ���
			while(taskQueue_.size() > 0) {
				std::cv_status waitResult = notEmpty_.wait_for(lock, std::chrono::seconds(1));
				// ���ֳ�ʱ���ػ�������ִ���귵��
				if (std::cv_status::timeout == waitResult) {
					auto nowTime = std::chrono::high_resolution_clock().now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(nowTime - lastTime);
					// ���̵߳Ŀ���ʱ�䳬�����ֵ���ҵ�ǰ�̳߳ص��߳��������ڳ�ʼ�߳���������ʼ�����߳�
					if (duration.count() > THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_) {
						// ���̼߳�����ɾ��ָ�����߳�
						threads_.erase(threadId);
						// ���¿����̵߳�����
						idleThreadSize_--;
						// ���µ�ǰ�̳߳ص��߳�����
						curThreadSize_--;
						// ��ӡ��־��Ϣ
						std::cout << "thread " << threadId << " exited." << std::endl;
						return;
					}
				}
			}
		}
		else {
			// �ȴ�������в�Ϊ��
			notEmpty_.wait(lock, [this]() { return taskQueue_.size() > 0; });
		}

		// �����߳�������һ���߳�ִ������֮ǰ��
		idleThreadSize_--;

		// ����������л�ȡ��Ҫִ�е�����
		std::shared_ptr<Task> task = taskQueue_.front();

		// �����������������Ƴ�
		taskQueue_.pop();
		taskSize_--;

		std::cout << "thread " << std::this_thread::get_id() << " �ɹ���ȡ����..." << std::endl;

		// �����ȡ������֮������������ɲ�Ϊ�գ������֪ͨ�����߳�ִ������
		if (taskQueue_.size() > 0) {
			notEmpty_.notify_all();
		}

		// ��Ϊ�ջ�ȡ������������п϶��п���λ�ã���������֪ͨ�û��ύ�����̳߳�
		notFull_.notify_all();

		// �ͷŻ��������ڵ�ǰ�߳�ִ������֮ǰ��
		lock.unlock();

		// ��ǰ�̸߳���ִ������
		if (task != nullptr) {
			task->exec();
		}

		// �����߳�������һ���߳�ִ��������֮��
		idleThreadSize_++;

		// �����̳߳����ִ���������ʱ��
		lastTime = std::chrono::high_resolution_clock().now();
	}
}

// �ύ������̳߳�
std::shared_ptr<Result> ThreadPool::submitTask(std::shared_ptr<Task> task) {
	// ��ȡ������
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// �ȴ���������п���λ�ã�������
	bool waitResult = notFull_.wait_for(lock, std::chrono::seconds(1), [this]() { return taskQueue_.size() < taskQueMaxThreshHold_; });
	if (!waitResult) {
		std::cerr << "task queue is full, submit task failed.";
		return std::make_shared<Result>(task, false);
	}

	// �����������п���λ�ã���������������������������
	taskQueue_.emplace(task);
	taskSize_++;

	// ��Ϊ�շ�����������������п϶���Ϊ�գ�֪ͨ�̳߳��е��߳�ȥִ������
	notEmpty_.notify_all();

	// Cacheģʽ�Ĵ�����������������̬�����̳߳ص��߳�����
	if (PoolMode::MODE_CACHED == poolMode_ && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeMaxThreshHold_) {
		// ��ӡ��־��Ϣ
		std::cout << "create new thread." << std::endl;
		// �������̶߳��󣬲����̴߳��������ݸ��̶߳���Ĺ��캯��
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
		// ��ȡ�߳�ID�������ڽ��̷߳����̼߳���֮ǰ��ȡһ���߳�ID�������������ȡ����ֵ��
		int threadId = thread->getId();
		// �����̶߳�������̼߳�����
		threads_.emplace(threadId, std::move(thread));
		// �������߳�
		threads_[threadId]->start();
		// ���¿����̵߳�����
		idleThreadSize_++;
		// ���µ�ǰ�̳߳ص��߳�����
		curThreadSize_++;
	}

	// ��������ִ�н��
	return std::make_shared<Result>(task);
}


////////////////////////////////////////// �߳��� /////////////////////////////////////////////


// �̹߳���
Thread::Thread(ThreadHandler handler) : threadHandler_(handler),threadId_(generateId_++) {

}

// �߳�����
Thread::~Thread() {

}

// �����߳�
void Thread::start() {
	// ����һ���̣߳���ִ���̴߳�����
	std::thread t(threadHandler_, threadId_);

	// �����߳�����Ϊ�����߳�
	t.detach();
}


// ��ȡ�߳�ID
int Thread::getId() const {
	return threadId_;
}

// ���ڸ�������ȫ��Ψһ���߳�ID
int Thread::generateId_ = 0;


////////////////////////////////////////// ��������� /////////////////////////////////////////////


// ���캯��
Task::Task() : result_(nullptr) {

}

// ִ������
void Task::exec() {
	// ִ���������߼���������̬���ã�
	Any data = run();

	// ��������ִ�н��
	if (result_ != nullptr) {
		result_->setVal(std::move(data));
	}
}

// ��������ִ�н��
void Task::setResult(Result * p) {
	result_ = p;
}


////////////////////////////////////////// �������� /////////////////////////////////////////////


// ���캯��
Result::Result(std::shared_ptr<Task> task, bool isValid) : task_(task), isValid_(isValid) {
	// �������������ִ�н��
	task->setResult(this);
}

// ��ȡ����ִ�н��
Any Result::get() {
	// �������ִ�н����Ч��ֱ�ӷ���
	if (!isValid_) {
		// TODO �Ż�����
		return "";
	}

	// �ȴ���ȡһ���ź�����Դ�����õ�ǰ�̵߳ȴ�����ִ�н����
	sem_.wait();

	// ��������ִ�н��
	return std::move(data_);
}

// ��������ִ�н��
void Result::setVal(Any data) {
	// �洢����ִ�н��
	data_ = std::move(data);

	// ����һ���ź�����Դ����֪ͨ�����̻߳�ȡ����ִ�н����
	sem_.post();
}

// ��ȡ����ִ�н���Ƿ���Ч
bool Result::isValid() const {
	return isValid_;
}
