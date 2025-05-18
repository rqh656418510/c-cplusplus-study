
#include<iostream>
#include<functional>
#include<thread>
#include<memory>
#include<mutex>
#include"thread_pool.h"

////////////////////////////////////////// �̳߳��� ////////////////////////////////////////////

// �̳߳ع���
ThreadPool::ThreadPool() {
	initThreadSize_ = INIT_THREAD_SIZE;
	taskSize_ = 0;
	taskQueMaxThreshHold_ = TASK_MAX_THRESHHOLD;
	poolMode_ = PoolMode::MODE_FIXED;
}

// �̳߳�����
ThreadPool::~ThreadPool() {

}

// �����̳߳صĹ���ģʽ
void ThreadPool::setMode(PoolMode mode) {
	poolMode_ = mode;
}

// ����������е��������
void ThreadPool::setTaskQueMaxThreshHold(size_t size) {
	taskQueMaxThreshHold_ = size;
}

// �����̳߳�
void ThreadPool::start(int initThreadSize) {
	// ��¼��ʼ���߳�����
	initThreadSize_ = initThreadSize;

	// ������ʼ���߳�
	for (int i = 0; i < initThreadSize_; ++i) {
		// �����̶߳��󣬲����̴߳��������ݸ��̶߳���Ĺ��캯��
		std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this));
		// ���̶߳�������߳��б���
		threads_.emplace_back(std::move(thread));
	}

	// ������ʼ���߳�
	for (int i = 0; i < initThreadSize_; ++i) {
		threads_[i]->start();
	}
}

// �̴߳�����������ִ������
void ThreadPool::threadHandler() {
	// ��ѭ��
	for (;;) {
		// ��ȡ������
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		std::cout << "thread " << std::this_thread::get_id() << " �ȴ���ȡ����..." << std::endl;

		// �ȴ�������в�Ϊ��
		notEmpty_.wait(lock, [this]() { return taskQueue_.size() > 0; });

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

	// ��Ϊ�շ�����������������п϶���Ϊ�գ�֪ͨ�̳߳ط����߳�ȥִ������
	notEmpty_.notify_all();

	// ��������ִ�н��
	return std::make_shared<Result>(task);
}


////////////////////////////////////////// �߳��� /////////////////////////////////////////////


// �̹߳���
Thread::Thread(ThreadHandler handler) : threadHandler_(handler) {

}

// �߳�����
Thread::~Thread() {

}

// �����߳�
void Thread::start() {
	// ����һ���̣߳���ִ���̴߳�����
	std::thread t(threadHandler_);

	// �����߳�����Ϊ�����߳�
	t.detach();
}


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
