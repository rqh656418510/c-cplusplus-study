/*
 * 1. queue容器的常用操作
*/

#include <iostream>
#include <queue>

using namespace std;

void printQueue(queue<int> &q) {
    // 判断队列是否为空
    while (!q.empty()) {
        cout << "大小: " << q.size() << endl;
        cout << "队头: " << q.front() << endl;
        cout << "队尾: " << q.back() << endl;
        // 弹出（删除）队头元素
        q.pop();
    }

}

int main() {
    // 默认构造函数
    queue<int> q1;

    // 往队尾添加元素
    q1.push(1);
    q1.push(3);
    q1.push(5);
    q1.push(7);
    q1.push(9);

    // 返回队列的大小
    cout << "size = " << q1.size() << endl;

    // 返回第一个元素
    cout << "first = " << q1.front() << endl;

    // 返回最后一个元素
    cout << "last = " << q1.back() << endl;

    printQueue(q1);

    // 拷贝构造函数
    queue<int> q2 = q1;

    return 0;
}
