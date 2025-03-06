/**
 * 多线程访问共享对象的线程安全问题
 */

#include <iostream>
#include <memory>
#include <thread>

using namespace std;

// 线程安全问题的解决

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

void executTask(weak_ptr<Task> wp) {
    // 子线程等待 5 秒
    this_thread::sleep_for(chrono::seconds(5));

    // 子线程访问共享对象时，先检查共享对象是否存活
    shared_ptr<Task> sp = wp.lock();
    if (sp != nullptr) {
        sp->run();
    }
    else {
		cout << "Failed to invoke Task:run()";
    }
}

int main() {
    {
        // 创建强引用智能指针
        shared_ptr<Task> task = make_shared<Task>();

        // 创建子线程
        thread t(executTask, weak_ptr<Task>(task));

        // 将子线程与 thread 对象分离，使其在后台独立运行，直到子线程执行完毕
        t.detach();

    } // 共享对象 task 出了作用域后会自动释放
    
    // 主线程等待子线程执行完成
    this_thread::sleep_for(chrono::seconds(10));

    return 0;
}