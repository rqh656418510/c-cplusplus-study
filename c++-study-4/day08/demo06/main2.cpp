/**
 * 详解decltype含义，decltype主要用途
 *
 * (b) decltype 作用于表达式
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
    int x = 0;
    int& r = x;
    const int c = 1;

    // 案例 1：decltype 作用于字面量（纯右值）——返回其类型本身，非引用
    decltype(5) a = 0;  // decltype(5) = int，a 类型为 int
    print_type<decltype(a)>("decltype(a)");

    // 案例 2：decltype 作用于左值表达式（带括号的变量），得到引用类型
    decltype((x)) b = x;  // 变量名 x 单独用时是 int，但 (x) 是左值表达式，decltype((x)) 返回 int&，b 类型为 int&
    print_type<decltype(b)>("decltype(b)");

    // 案例 3：decltype 作用于赋值表达式——赋值返回左值，得到引用类型
    decltype(x = 5) d = x;  // decltype(x = 5) = int&，d 类型为 int&
    print_type<decltype(d)>("decltype(d)");

    // 案例 4：decltype 作用于前置自增表达式——返回左值，得到引用类型
    decltype(++x) e = x;  // decltype(++x) = int&，e 类型为 int&
    print_type<decltype(e)>("decltype(e)");

    // 案例 5：decltype 作用于后置自增表达式——返回纯右值，得到非引用类型
    decltype(x++) f = 0;  // decltype(x++) = int，f 类型为 int
    print_type<decltype(f)>("decltype(f)");

    // 案例 6：decltype 作用于算术表达式——返回纯右值，得到非引用类型
    decltype(x + c) g = 0;  // decltype(x + c) = int，g 类型为 int
    print_type<decltype(g)>("decltype(g)");

    // 案例 7：decltype 作用于返回右值引用的函数调用（结果为将亡值）
    decltype(std::move(x)) h = 0;  // std::move 返回 int&&，h 类型为 int&&
    print_type<decltype(h)>("decltype(h)");

    // 案例 8：decltype 作用于解引用表达式——返回左值，得到引用类型
    int* p = &x;
    decltype(*p) i = x;  // decltype(*p) = int&，i 类型为 int&
    print_type<decltype(i)>("decltype(i)");

    // 案例 9：decltype 作用于三元表达式——两个分支均为左值时返回左值
    decltype(true ? x : x) j = x;  // decltype(true ? x : x) = int&，j 类型为 int&
    print_type<decltype(j)>("decltype(j)");

    // 案例 10：decltype 作用于逗号表达式——结果为最后一个表达式的类型和值类别
    decltype((void)x, x) k = x;  // 逗号表达式结果为左值 x，k 类型为 int&
    print_type<decltype(k)>("decltype(k)");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
