/**
 * 可变参数函数、initializer_list、省略号形参
 *
 * (a) 可变参数函数
 */

#include <iostream>
#include <string>
#include <utility>

// ============================================================
// 实现方式一：递归展开（C++ 11 起支持）
// ============================================================

// 递归终止条件：只剩一个参数时直接返回
template <typename T>
T sum_recursive(T v) {
    return v;
}

// 递归情形：取出第一个参数 head，对剩余参数包 tail... 递归求和
template <typename T, typename... Args>
T sum_recursive(T head, Args... tail) {
    return head + sum_recursive(tail...);  // tail... 在编译期展开为实参列表
}

// ============================================================
// 实现方式二：完美转发 —— 保持实参的值类别与类型
// ============================================================

// 递归终止：处理最后一个参数
template <typename T>
void print_all(T&& last) {
    std::cout << std::forward<T>(last) << std::endl;
}

// 递归情形：转发当前参数，再递归处理剩余参数
// T&& 为转发引用，std::forward 保持左值/右值属性
template <typename T, typename... Args>
void print_all(T&& head, Args&&... tail) {
    std::cout << std::forward<T>(head) << ' ';
    print_all(std::forward<Args>(tail)...);
}

// ============================================================
// 补充：sizeof... 获取参数包中参数个数
// ============================================================
template <typename... Args>
constexpr std::size_t count_args(Args&&...) {
    return sizeof...(Args);  // 编译期得到参数个数
}

int main() {
    std::cout << sum_recursive(1, 2, 3, 4, 5) << std::endl;
    print_all(42, "hello", "world", 3.14);
    std::cout << "arg count = " << count_args(1, 'a', 3.0) << std::endl;
    return 0;
}