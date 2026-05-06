/*
 * 可变参模板
 *
 * (b) 可变参函数模板
 */

#include <iostream>

using namespace std;

// 递归终止函数
void print() {
    cout << "print()" << endl;
}

// 定义可变参函数模板
template <typename T, typename... Args>
void print(T first, Args... args) {
    cout << first << endl;
    // 递归调用，展开参数包
    print(args...);
}

int main() {
    print(2, 3.14, "hello", 5);
    return 0;
}