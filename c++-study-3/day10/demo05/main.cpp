/**
 * 多线程访问共享对象的线程安全问题
 */

#include <iostream>
#include <memory>
#include <thread>

using namespace std;

// 线程安全问题的产生

class Task {

public:
    Task() {
        cout << "Task()" << endl;
    }

    ~Task() {
		cout << "~Task()" << endl;
    }

    void run() {
        cout << "invoke Task::run()" << endl;
    }

};

void executTask(Task* task) {
    // 子线程等待 5 秒
    this_thread::sleep_for(chrono::seconds(5));
    // 执行任务方法
    task->run();
}

int main() {
    Task* task = new Task();

    // 创建子线程
	thread t(executTask, task);

    // 将子线程与 thread 对象分离，使其在后台独立运行，直到子线程执行完毕
    t.detach();

    // 主线程在子线程调用 Task::run() 函数之前析构 Task 对象（共享对象），这样就会产生线程安全问题
    delete task;

    // 等待子线程执行完成
    t.join();

    return 0;
}