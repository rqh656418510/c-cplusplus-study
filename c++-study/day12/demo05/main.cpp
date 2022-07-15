/*
 * 1. stack容器的常用操作
*/

#include<iostream>
#include<stack>

using namespace std;

void printStack(stack<int> &s) {
    // 判断容器是否为空
    while (!s.empty()) {
        // 获取栈顶元素
        cout << s.top() << " ";
        // 弹出栈顶元素（弹栈）
        s.pop();
    }
    cout << endl;
}

int main() {
    // 默认构造函数
    stack<int> s1;

    // 向栈顶添加元素（压栈）
    s1.push(5);
    s1.push(12);
    s1.push(24);
    s1.push(35);
    s1.push(46);

    printStack(s1);

    // 拷贝构造函数
    stack<int> s2 = s1;

    return 0;
}