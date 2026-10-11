/**
 * 详解decltype含义，decltype主要用途
 *
 * (a) decltype 作用于变量名（未加括号）
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

// 自定义类
class MyClass {
public:
    float i;
    double j;
};

// 辅助打印推导类型（保留 const/volatile/引用 属性）
template <typename T>
void print_type(const char* name) {
    std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main() {
    int x = 0;
    int y = 0;
    const int a = 1;
    const int& b = a;
    MyClass my_class;

    // 案例 1：auto 值传递，顶层 const 和引用均被丢弃
    auto c = a;  // auto = int，c 类型为 int
    print_type<decltype(c)>("decltype(c)");

    // 案例 2：decltype 作用于变量名
    decltype(a) d = 15;  // decltype(a) = const int，d 类型为 const int
    print_type<decltype(d)>("decltype(d)");

    // 案例 3：decltype 作用于引用变量名
    decltype(b) e = d;  // decltype(b) = const int&，e 类型为 const int&
    print_type<decltype(e)>("decltype(e)");

    // 案例 4：decltype 作用于类类型对象
    decltype(my_class) f;  // decltype(my_class) = MyClass，f 类型为 MyClass
    print_type<decltype(f)>("decltype(f)");

    // 案例 5：decltype 作用于类数据成员
    decltype(MyClass::i) g = 5.0;  // decltype(MyClass::i) = float，g 类型为 float
    print_type<decltype(g)>("decltype(g)");

    // 案例 6：auto&& 作为万能引用绑定左值
    auto&& h = x;  // auto = int&，int& && 经引用折叠变为 int&，h 类型为 int&
    print_type<decltype(h)>("decltype(h)");

    // 案例 7
    decltype(h)&& i = y;  // decltype(h) = int&，int& && 经引用折叠变为 int&，i 类型为 int&
    print_type<decltype(i)>("decltype(i)");

    // 案例 8：auto 推导数组——数组退化为指针
    int arr[3] = {1, 2, 3};
    auto k = arr;  // arr 退化为指向首元素的指针，auto = int*，k 类型为 int*
    print_type<decltype(k)>("decltype(k)");

    // 案例 9：decltype 作用于数组名——保留完整数组类型，不退化为指针
    decltype(arr) l;  // decltype(arr) = int[3]，l 类型为 int[3]
    print_type<decltype(l)>("decltype(l)");

    // 案例 10：decltype 作用于数组下标表达式——返回左值，得到元素引用类型
    decltype(arr[0]) m = x;  // decltype(arr[0]) = int&，m 类型为 int&
    print_type<decltype(m)>("decltype(m)");

    // 案例 11：decltype 作用于数组名加括号——退化为左值表达式，得到数组引用类型
    decltype((arr)) n = arr;  // decltype((arr)) = int(&)[3]，n 类型为 int(&)[3]
    print_type<decltype(n)>("decltype(n)");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
