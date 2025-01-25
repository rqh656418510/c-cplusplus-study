/**
 * 详解容器适配器
 *
 * <p> priority_queue（优先级队列）的使用
 */

#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 优先级队列
    priority_queue<int> pque;

    for (int i = 0; i < 20; i++) {
        int item = rand() % 100 + 1;
        // 入队
        pque.push(item);
        cout << item << " ";
    }
    cout << endl;

    // 返回队列的元素个数
    cout << "size: " << pque.size() << endl;

    // 判断队列是否为空
    while (!pque.empty()) {
        // 获取队头元素
        cout << pque.top() << " ";
        // 出队
        pque.pop();
    }

    return 0;
}
