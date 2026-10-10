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
    auto fp1 = add;  // add 类型为 int(int, int)，按值推导时函数退化为 int(*)(int, int)，故 auto = int(*)(int, int)，fp1 类型为 int(*)(int, int)
    print_type<decltype(fp1)>("auto fp1 = add");

    // 案例 2：const auto 推导函数名，const 修饰函数指针本身
    const auto fp2 = add;  // auto = int(*)(int, int)，加上显式 const，fp2 类型为 int(* const)(int, int)
    print_type<decltype(fp2)>("const auto fp2 = add");

    // 案例 3：auto& 推导函数名（引用方式），保留函数类型
    auto& fp3 = add;  // auto& 绑定到函数本身，auto = int(int, int)，fp3 类型为 int(&)(int, int)
    print_type<decltype(fp3)>("auto& fp3 = add");

    // 案例 4：auto* 推导函数名（指针方式）
    auto* fp4 = add;  // add 是函数左值，auto* 根据声明形式推导出 auto 为函数类型 int(int, int)，最终 fp4 的类型为 int(*)(int, int)，即指向函数的指针
    print_type<decltype(fp4)>("auto* fp4 = add");

    // 案例 5：auto&& 推导函数名（万能引用，左值）
    auto&& fp5 = add;  // add 是左值，auto&& 推 auto = int(&)(int, int)，经引用折叠后 fp5 类型为 int(&)(int, int)
    print_type<decltype(fp5)>("auto&& fp5 = add");

    // 案例 6：auto 推导无捕获的 lambda，得到闭包类型（非函数指针）
    auto fp6 = [](int x) { return x * 2; };  // 闭包类型唯一且匿名，auto = 该闭包类型，fp6 类型为该闭包类型
    print_type<decltype(fp6)>("auto fp6 = [](int x){ return x*2; }");

    // 案例 7：auto 推导有捕获的 lambda，同样得到唯一的闭包类型
    int y = 10;
    auto fp7 = [y](int x) { return x + y; };  // 闭包类型唯一且匿名（且含捕获成员），auto = 该闭包类型，fp7 类型为该闭包类型
    print_type<decltype(fp7)>("auto fp7 = [y](int x){ return x + y; }");

    // 案例 8：auto& 推导有捕获的 lambda，保留闭包类型引用
    auto& fp8 = fp7;  // fp7 为闭包类型左值，auto& 绑定到该闭包对象本身，auto = 闭包类型，fp8 类型为该闭包类型的引用
    print_type<decltype(fp8)>("auto& fp8 = fp7");

    // 案例 9：无捕获的 lambda 可隐式转换为函数指针
    int (*fp9)(int) = fp6;  // fp6 为闭包类型（无捕获），可转换为 int(*)(int)，fp9 类型为 int(*)(int)
    print_type<decltype(fp9)>("int (*fp9)(int) = fp6");

    // 案例 10：有捕获的 lambda 不能隐式转换为函数指针（编译错误）
    // int (*fp10)(int) = fp7;   // 编译失败：有捕获的 lambda 不能转为函数指针

    return 0;
}

#else
int main() {
    return 0;
}
#endif
