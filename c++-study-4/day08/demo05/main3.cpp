/**
 * 理解auto类型推断，auto应用场合
 *
 * (c) auto - 函数类型推导
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

// 辅助打印推导类型（保留 const/volatile/引用 属性）
template <typename T>
void print_type(const char* name) {
    std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

// 普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 案例 1：auto 推导函数名（传值方式），函数退化为函数指针
    auto fp = add;  // add 类型为 int(int, int)，按值推导时函数退化为 int(*)(int, int)，故 auto = int(*)(int, int)，fp 类型为 int(*)(int, int)
    print_type<decltype(fp)>("auto fp = add");

    // 案例 2：const auto 推导函数名，const 修饰函数指针本身
    const auto fp2 = add;  // auto = int(*)(int, int)，加上显式 const，fp2 类型为 int(* const)(int, int)
    print_type<decltype(fp2)>("const auto fp2 = add");

    // 案例 3：auto& 推导函数名（引用方式），保留函数类型
    auto& fr = add;  // auto& 绑定到函数本身，auto = int(int, int)，fr 类型为 int(&)(int, int)
    print_type<decltype(fr)>("auto& fr = add");

    // 案例 4：auto* 推导函数名（指针方式），先退化为函数指针再匹配
    auto* fp3 = add;  // add 退化为 int(*)(int, int)，与 auto* 匹配得 auto = int(int, int)，故 fp3 类型为 int(*)(int, int)
    print_type<decltype(fp3)>("auto* fp3 = add");

    // 案例 5：auto&& 推导函数名（万能引用，左值）
    auto&& fr2 = add;  // add 是左值，auto&& 推 auto = int(&)(int, int)，折叠后 fr2 类型为 int(&)(int, int)
    print_type<decltype(fr2)>("auto&& fr2 = add");

    // 案例 6：auto 推导无捕获的 lambda，得到闭包类型（非函数指针）
    auto lam = [](int x) { return x * 2; };  // 闭包类型唯一且匿名，auto = 该闭包类型，lam 类型为该闭包类型
    print_type<decltype(lam)>("auto lam = [](int x){ return x*2; }");

    // 案例 7：无捕获的 lambda 可隐式转换为函数指针
    int (*fp4)(int) = lam;  // lam 为闭包类型，可转换为 int(*)(int)，fp4 类型为 int(*)(int)
    print_type<decltype(fp4)>("int (*fp4)(int) = lam");

    // 案例 8：有捕获的 lambda 不能转换为函数指针（编译错误，仅作说明）
    // int y = 10;
    // auto lam2 = [y](int x) { return x + y; };
    // int (*fp5)(int) = lam2;   // 编译失败：有捕获的 lambda 不能转为函数指针

    return 0;
}

#else
int main() {
    return 0;
}
#endif
