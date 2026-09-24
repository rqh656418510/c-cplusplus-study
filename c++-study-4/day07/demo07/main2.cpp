/**
 * 适配器概念、分类、范例及总结
 *
 * (b) queue 适配器的使用
 */

#include <iostream>
#include <queue>

int main() {
    // 队列容器（先进先出 - FIFO）
    std::queue<int> que;

    for (int i = 0; i < 5; ++i) {
        // 入队
        que.push(i);
    }

    while (!que.empty()) {
        // 获取队头的元素
        std::cout << que.front() << " ";
        // 出队
        que.pop();
    }

    return 0;
}
