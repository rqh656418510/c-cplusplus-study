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
    const auto& qx = x;

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

    // 案例 7：const auto& 本身是 const 引用，用 auto（非引用）推导时
    auto a7 = qx;  // auto = int（引用和 const 均被忽略），a7 类型为 int
    print_type<decltype(a7)>("auto a7 = qx");

    // 案例 8：auto& 推导 const 引用
    auto& a8 = qx;  // auto = const int（const 被保留），a8 类型为 const int&
    print_type<decltype(a8)>("auto& a8 = qx");

    // 案例 9：auto 用于 new 表达式
    auto a9 = new auto(100);  // new 后的 auto 根据初始值 100 被推导为 int，new 表达式返回 int*，故 a9 类型为 int*
    print_type<decltype(a9)>("auto a9 = new auto(100)");

    // 案例 10：const auto* 指针推导
    const auto* a10 = &x;  // auto = int，a10 类型为 const int*
    print_type<decltype(a10)>("const auto* a10 = &x");

    // 案例 11：auto&& 万能引用绑定左值
    auto&& a11 = x;  // x 是 int 类型的左值，auto&& 遇到左值时，auto 被推导为 int&，再经过引用折叠 int& && 变成 int&，故 a11 类型为 int&
    print_type<decltype(a11)>("auto&& a11 = x");

    // 案例 12：auto&& 万能引用绑定 const 左值
    auto&& a12 = cx;  // cx 类型为 const int，是 const 左值，auto&& 遇到左值时 auto 推导为 const int&，再经过引用折叠 const int& && 变成 const int&，故 a12 类型为 const int&
    print_type<decltype(a12)>("auto&& a12 = cx");

    // 案例 13：auto&& 绑定右值（纯右值）
    auto&& a13 = 100;  // 100 是 int 类型的纯右值，auto&& 遇到右值时 auto 被推导为 int，代入 auto&& 得到 int&&，无需经过引用折叠，故 a13 类型为 int&&
    print_type<decltype(a13)>("auto&& a13 = 100");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
