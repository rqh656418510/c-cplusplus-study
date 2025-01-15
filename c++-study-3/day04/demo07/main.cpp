/**
 * 重载new和delete运算符来实现对象池
 */
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Queue {

public:
    Queue() {
        cout << "Queue()" << endl;
        _size = 0;
        _front = _rear = new QueueItem();
    }

    ~Queue() {
        cout << "~Queue()" << endl;
        while (_front != nullptr) {
            QueueItem *next = _front->_next;
            delete _front;
            _front = next;
        }
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
        if (empty()) {
            throw runtime_error("Queue is empty, cannot pop");
        }

        QueueItem *first = _front->_next;
        _front->_next = first->_next;
        if (_front->_next == nullptr) {
            _rear = _front;
        }
        delete first;
        _size--;
    }

    // 返回头节点
    T front() const {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return _front->_next->_data;
    }

    // 队列是否为空
    bool empty() const {
        return _front == _rear;
    }

    // 获取队列的大小
    size_t size() {
        return _size;
    }

private:
    // 队列元素
    struct QueueItem {
        QueueItem(T data = T()) : _data(data), _next(nullptr) {

        };

        // 自定义 QueueItem 对象的内存开辟
        void *operator new(size_t size) {
            if (_itemPool == nullptr) {
                // 初始化对象池
                _itemPool = (QueueItem *) new char[sizeof(QueueItem) * ITEM_POOL_SIZE];
                QueueItem *p = _itemPool;
                for (; p < _itemPool + ITEM_POOL_SIZE - 1; ++p) {
                    p->_next = p + 1;
                }
                // 处理最后一个节点
                p->_next = nullptr;
            }

            QueueItem *ptr = _itemPool;
            _itemPool = _itemPool->_next;
            return ptr;
        }

        // 自定义 QueueItem 对象的内存释放
        void operator delete(void *ptr) {
            // 归还给对象池
            QueueItem *p = (QueueItem *) ptr;
            p->_next = _itemPool;
            _itemPool = p;
        }

        T _data;                                    // 当前节点的数据
        QueueItem *_next;                           // 下一个节点
        static QueueItem *_itemPool;                // 指向对象池中未使用的第一节点
        static const int ITEM_POOL_SIZE = 10000;    // 对象池的大小
    };

    QueueItem *_front;  // 头结点，是一个虚拟节点，用于简化队列操作（如插入和删除）
    QueueItem *_rear;   // 尾节点，是一个真实节点，始终指向队列的最后一个有效节点，或者在队列为空时指向虚拟头节点
    int _size;          // 队列的大小

};

template<typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

void test01() {
    cout << "============ test01() ============" << endl;

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

void test02() {
    cout << "============ test02() ============" << endl;

    Queue<int> queue;

    // 如果这里不使用对象池，那么就会频繁开辟和释放对象的内存空间，导致性能消耗比较严重
    for (int i = 0; i < 1000; i++) {
        int value = random() % 100 + 1;
        queue.push(value);
        queue.pop();
    }

    cout << (queue.empty() ? "empty" : "not empty") << endl;
}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    test01();
    test02();

    return 0;
}
