/**
 * bind和function实现线程池
 */

#include <iostream>
#include <functional>
#include <vector>
#include <thread>

using namespace std;

// 自定义线程
class Thread {

public:

	Thread(function<void(int)> func, int id) : _func(func), _id(id) {

    }

    // 创建子线程
    thread start() {
        thread t(_func, _id);
        return t;
    }

private:
	function<void(int)> _func;
    int _id;
};

// 自定义线程池
class ThreadPool {

public:

    ThreadPool() {

    }

    ~ThreadPool() {
        // 释放堆上的资源
        for (int i = 0; i < _pool.size(); i++) {
            delete _pool[i];
        }
    }

    void startPool(int size) {
        // 创建自定义的线程对象，并放入容器
        for (int i = 0; i < size; i++) {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, placeholders::_1), i));
        }

        // 创建子线程
        for (int i = 0; i < size; i++) {
            _handler.push_back(_pool[i]->start());
        }

        // 等待子线程执行完成
        for (thread &t : _handler) {
            t.join();
        }
    }

private:
    vector<Thread*>  _pool;
    vector<thread> _handler;

    // runInThread() 成员函数充当线程函数
    void runInThread(int id) {
        cout << "call runInThread! id: " << id << endl;
    }
};

int main() {
    ThreadPool pool;
    pool.startPool(10);

    return 0;
}
