/**
 * 详解容器适配器
 *
 * <p> queue（队列）的使用
 */

#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 队列（先进先出 - FIFO）
    queue<int> q1;

    for (int i = 0; i < 20; i++) {
        int item = rand() % 100 + 1;
        // 入队
        q1.push(item);
        cout << item << " ";
    }
    cout << endl;

    // 返回队列的元素个数
    cout << "size: " << q1.size() << endl;

    // 判断队列是否为空
    while (!q1.empty()) {
        // 获取队头元素
        cout << q1.front() << " ";
        // 出队
        q1.pop();
    }

    return 0;
}
