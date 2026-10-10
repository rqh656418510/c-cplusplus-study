/**
 * 理解auto类型推断，auto应用场合
 *
 * (d) auto - 特殊类型推导
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <initializer_list>
#include <iostream>

// 辅助打印推导类型（保留 const/volatile/引用 属性）
template <typename T>
void print_type(const char* name) {
    std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main() {
    // 案例 1：auto 推导花括号初始化列表，推导为 std::initializer_list<int>
    auto a1 = {1, 2, 3};  // auto = std::initializer_list<int>，a1 类型为 std::initializer_list<int>
    print_type<decltype(a1)>("auto a1 = {1, 2, 3}");

    // 案例 2：auto 推导单元素花括号初始化列表，仍推导为 std::initializer_list<int>
    auto a2 = {10};  // auto = std::initializer_list<int>，a2 类型为 std::initializer_list<int>
    print_type<decltype(a2)>("auto a2 = {10}");

    // 案例 3：auto 推导显式指定类型的 std::initializer_list 对象
    std::initializer_list<int> list = {1, 2, 3};
    auto a3 = list;  // auto = std::initializer_list<int>，a3 类型为 std::initializer_list<int>
    print_type<decltype(a3)>("auto a3 = list");

    // 案例 4：const auto 推导花括号初始化列表，列表对象本身具有 const 属性
    const auto a4 = {1, 2, 3};  // auto = std::initializer_list<int>，a4 类型为 const std::initializer_list<int>
    print_type<decltype(a4)>("const auto a4 = {1, 2, 3}");

    // 案例 5：auto& 引用花括号初始化列表对象
    auto& a5 = a1;  // auto = std::initializer_list<int>，a5 类型为 std::initializer_list<int>&
    print_type<decltype(a5)>("auto& a5 = a1");

    // 案例 6：auto&& 万能引用绑定花括号初始化列表对象的左值
    auto&& a6 = a1;  // a1 是左值，auto 推导为 std::initializer_list<int>&，经引用折叠后 a6 类型为 std::initializer_list<int>&
    print_type<decltype(a6)>("auto&& a6 = a1");

    // 案例 7：auto 推导元素类型不一致的花括号初始化列表（编译错误）
    // auto a7 = {1, 2.5};  // 编译失败：std::initializer_list 的元素类型无法统一推导

    return 0;
}

#else
int main() {
    return 0;
}
#endif
