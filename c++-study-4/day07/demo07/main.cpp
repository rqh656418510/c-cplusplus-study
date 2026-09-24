/**
 * 适配器概念、分类、范例及总结
 *
 * (a) stack 适配器的使用
 */

#include <iostream>
#include <stack>

int main() {
    // 栈容器（先进后出 - LIFO）
    std::stack<int> st;

    for (int i = 0; i < 5; ++i) {
        // 入栈
        st.push(i);
    }

    while (!st.empty()) {
        // 获取栈顶的元素
        std::cout << st.top() << " ";
        // 出栈
        st.pop();
    }

    return 0;
}