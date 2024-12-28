/**
 * 类和对象代码应用实践
 */

#include <iostream>

using namespace std;

// 循环队列
class MyQueue {

public:
    MyQueue(int size = 20) {
        _pQueue = new int[size];
        _front = 0;
        _rear = 0;
        _size = size;
    }

    // 删除拷贝构造函数，不让用户调用
    // MyQueue(const MyQueue &other) = delete;

    // 拷贝构造函数
    MyQueue(const MyQueue &other) {
        _front = other._front;
        _rear = other._rear;
        _size = other._size;
        _pQueue = new int[_size];
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            _pQueue[i] = other._pQueue[i];
        }
    }

    // 删除赋值运算符，不让用户调用
    // MyQueue &operator=(const MyQueue &other) = delete;

    // 赋值运算符重载
    MyQueue &operator=(const MyQueue &other) {
        if (this == &other) {
            return *this;
        }

        if (_pQueue != nullptr) {
            delete[]_pQueue;
        }

        _front = other._front;
        _rear = other._rear;
        _size = other._size;
        _pQueue = new int[_size];
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            _pQueue[i] = other._pQueue[i];
        }

        return *this;
    }

    ~MyQueue() {
        if (_pQueue != nullptr) {
            delete[] _pQueue;
            _pQueue = nullptr;
        }
    }

    // 入队操作
    void push(int value) {
        if (full()) {
            resize();
        }
        _pQueue[_rear] = value;
        // 循环队列
        _rear = (_rear + 1) % _size;
    }

    // 出队操作
    void poll() {
        if (empty()) {
            return;
        }
        // 循环队列
        _front = (_front + 1) % _size;
    }

    // 返回队头元素
    int front() {
        return _pQueue[_front];
    }

    // 队列是否已满
    bool full() {
        return (_rear + 1) % _size == _front;
    }

    // 队列是否为空
    bool empty() {
        return _front == _rear;
    }

private:
    int *_pQueue;   // 队列的内存空间
    int _front;     // 队头的位置
    int _rear;      // 队尾的位置
    int _size;      // 队列的大小

    // 扩容操作
    void resize() {
        int index = 0;
        int *pTemp = new int[_size * 2];
        // 循环队列
        for (int i = _front; i != _rear; i = (i + 1) % _size) {
            pTemp[index++] = _pQueue[i];
        }
        delete[] _pQueue;
        _pQueue = pTemp;
        _size *= 2;
        _front = 0;
        _rear = index;
    }
};

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    // 调用普通构造函数
    MyQueue q1;
    for (int i = 0; i < 20; i++) {
        q1.push(rand() % 100);
    }

    // 调用拷贝构造函数
    MyQueue q2(q1);

    // 赋值运算符重载
    MyQueue q3;
    q3 = q1;

    while (!q3.empty()) {
        cout << q3.front() << " ";
        q3.poll();
    }
    cout << endl;
    return 0;
}
