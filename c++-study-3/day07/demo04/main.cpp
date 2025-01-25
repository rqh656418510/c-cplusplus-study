/**
 * 详解容器适配器
 *
 * <p> stack（栈）的使用
 */

#include <iostream>
#include <stack>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 栈（后进先出 - LIFO）
    stack<int> s1;

    for (int i = 0; i < 20; i++) {
        int item = rand() % 100 + 1;
        // 入栈
        s1.push(item);
        cout << item << " ";
    }
    cout << endl;

    // 返回栈的元素个数
    cout << "size: " << s1.size() << endl;

    // 判断栈是否为空
    while (!s1.empty()) {
        // 获取栈顶元素
        cout << s1.top() << " ";
        // 弹栈
        s1.pop();
    }

    return 0;
}
