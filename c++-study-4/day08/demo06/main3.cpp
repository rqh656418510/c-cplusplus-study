/**
 * 详解decltype含义，decltype主要用途
 *
 * (c) decltype 作用于函数名（未加括号）
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <functional>
#include <iostream>

int f() {
    return 0;
}

int& g() {
    static int v = 0;
    return v;
}

void h(int) {
}

// 辅助打印推导类型（保留 const/volatile/引用 属性）
template <typename T>
void print_type(const char* name) {
    std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main() {
    // 案例 1：decltype 作用于返回 int 的函数名——返回函数类型本身
    decltype(f) a;  // decltype(f) = int()，a 类型为 int()
    print_type<decltype(a)>("decltype(a)");

    // 案例 2：decltype 作用于返回 int& 的函数名——保留返回引用
    decltype(g) b;  // decltype(g) = int&()，b 类型为 int&()
    print_type<decltype(b)>("decltype(b)");

    // 案例 3：decltype 作用于带参数的函数名——参数列表也是函数类型的一部分
    decltype(h) c;  // decltype(h) = void(int)，c 类型为 void(int)
    print_type<decltype(c)>("decltype(c)");

    // 案例 4：decltype 作用于函数名后显式加 *——得到函数指针类型
    decltype(f)* d = f;  // decltype(f)* = int(*)(), d 类型为 int(*)()
    print_type<decltype(d)>("decltype(d)");

    // 案例 5：decltype 作用于函数名后显式加 &——得到函数引用类型
    decltype(f)& e = f;  // decltype(f)& = int(&)(), e 类型为 int(&)()
    print_type<decltype(e)>("decltype(e)");

    // 案例 6：decltype 作用于加括号的函数名——退化为左值表达式，返回函数引用
    decltype((f)) i = f;  // decltype((f)) = int(&)(), i 类型为 int(&)()
    print_type<decltype(i)>("decltype(i)");

    // 案例 7：decltype 结合 std::function 使用
    std::function<decltype(f)> j = f;  // decltype(f) = int()，作为模板参数传入 std::function，得到 std::function<int()>，j 类型为 std::function<int()>，可用于包装函数 f
    print_type<decltype(j)>("decltype(j)");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
