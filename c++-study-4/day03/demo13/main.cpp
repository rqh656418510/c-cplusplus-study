/*
 * 可变参模板
 *
 * (a) 可变参函数模板
 */

#include <iostream>

using namespace std;

// 定义可变参函数模板
template <typename... Args>
void print1(Args... args) {
    // 获取模板参数的数量（第一种写法）
    cout << sizeof...(args) << endl;
}

// 定义可变参函数模板
template <typename T, typename... Args>
void print2(T first, Args... args) {
    // 获取模板参数的数量（第二种写法）
    cout << sizeof...(Args) << endl;
}

int main() {
    print1();
    print1(1, 33, 44.5);

    print2(1.2, "hello");
    print2(2.3, "hello", 5);

    return 0;
}