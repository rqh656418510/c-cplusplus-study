/**
 * 理解auto类型推断，auto应用场合
 *
 * (a) auto - 常规类型推导
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

// 辅助打印推导类型（保留 const/volatile/引用 属性）
template <typename T>
void print_type(const char* name) {
    std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main() {
    int x = 10;
    const int cx = x;
    const int& rx = x;

    // 案例 1：auto 推导基础类型
    auto a1 = x;  // auto = int
    print_type<decltype(a1)>("auto a1 = x");

    // 案例 2：auto 推导 const 变量（顶层 const 被丢弃）
    auto a2 = cx;  // auto = int（const 被忽略）
    print_type<decltype(a2)>("auto a2 = cx");

    // 案例 3：auto 推导 const 引用（引用和 const 全被丢弃）
    auto a3 = rx;  // auto = int（引用和 const 均被忽略）
    print_type<decltype(a3)>("auto a3 = rx");

    // 案例 4：显式加 const，保留 const 属性
    const auto a4 = x;  // auto = int，a4 类型为 const int
    print_type<decltype(a4)>("const auto a4 = x");

    // 案例 5：显式加引用，保留引用属性（const 依然保留）
    const auto& a5 = x;  // auto = int，a5 类型为 const int&
    print_type<decltype(a5)>("const auto& a5 = x");

    // 案例 6：auto& 推导 const 引用（const 被保留）
    auto& a6 = rx;  // auto = const int，a6 类型为 const int&
    print_type<decltype(a6)>("auto& a6 = rx");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
