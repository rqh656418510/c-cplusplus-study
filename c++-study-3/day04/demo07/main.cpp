/**
 * new和delete重载实现的对象池应用
 */
#include <iostream>

using namespace std;

template<typename T>
class Queue {

public:
    Queue() {
        _size = 0;
        _front = _rear = new QueueItem();
    }

    ~Queue() {

    }

    // 入队操作（插入尾节点）
    void push(const T &value) {
        QueueItem *item = new QueueItem(value);
        _rear->_next = item;
        _rear = item;
        _size++;
    }

    // 出队操作（移除头节点）
    void pop() {
        if (!empty()) {
            QueueItem *first = _front->_next;
            _front->_next = first->_next;
            if (_front->_next == nullptr) {
                _rear = _front;
            }
            delete first;
            _size--;
        }
    }

    // 返回头节点
    T front() const {
        T val = _front->_next->_data;
        return val;
    }

    // 队列是否为空
    bool empty() const {
        return _front == _rear;
    }

    // 获取队列的大小
    int size() {
        return _size;
    }

private:
    // 队列元素
    struct QueueItem {
        QueueItem(T data = T()) : _data(data), _next(nullptr) {

        };

        T _data;
        QueueItem *_next;
    };

    QueueItem *_front;  // 指向头节点
    QueueItem *_rear;   // 指向尾节点
    int _size;          // 队列的大小

};

void test01() {
    Queue<int> queue;

    for (int i = 0; i < 10; i++) {
        int value = random() % 100 + 1;
        queue.push(value);
        cout << value << " ";
    }
    cout << endl << "size = " << queue.size() << endl;

    while (!queue.empty()) {
        cout << queue.front() << " ";
        queue.pop();
    }
    cout << endl << "size = " << queue.size() << endl;
}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    test01();
    return 0;
}