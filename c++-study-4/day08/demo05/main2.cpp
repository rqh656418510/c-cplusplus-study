/**
 * 理解auto类型推断，auto应用场合
 *
 * (b) auto - 数组类型推导
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
    char arr1[] = "I Love C";
    const char arr2[] = "I Love C++";
    int arr3[] = {1, 2, 3};

    // 案例 1：auto 推导数组（传值方式），数组退化为指针
    auto str1 = arr1;  // arr1 类型为 char[9]，按值推导时数组退化为 char*，故 auto = char*，str1 类型为 char*
    print_type<decltype(str1)>("auto str1 = arr1");

    // 案例 2：auto& 推导数组（引用方式），保留数组类型
    auto& str2 = arr1;  // arr1 类型为 char[9]，auto& 绑定到数组本身，auto = char[9]，str2 类型为 char(&)[9]
    print_type<decltype(str2)>("auto str2 = arr1");

    // 案例 3：auto 推导 const 数组（传值方式），数组退化为指针，元素的 const 属性保留
    auto str3 = arr2;  // arr2 类型为 const char[11]，数组退化为指向首元素的指针，auto 推导为 const char*，str3 类型为 const char*
    print_type<decltype(str3)>("auto str3 = arr2");

    // 案例 4：auto& 推导 const 数组（引用方式），保留数组类型和 const
    auto& str4 = arr2;  // arr2 类型为 const char[11]，auto& 绑定到数组本身，auto = const char[11]，str4 类型为 const char(&)[11]
    print_type<decltype(str4)>("auto str4 = arr2");

    // 案例 5：auto 推导非字符数组（传值方式），同样会退化为指针
    auto str5 = arr3;  // arr3 类型为 int[3]，按值推导时数组退化为 int*，故 auto = int*，str5 类型为 int*
    print_type<decltype(str5)>("auto str5 = arr3");

    // 案例 6：auto&&（万能引用）推导非 const 左值数组
    auto&& str6 = arr1;  // arr1 类型为 char[9]，是左值；auto&& 遇到左值时 auto 推导为 char(&)[9]，与 && 发生引用折叠后仍为 char(&)[9]，故 str6 类型为 char(&)[9]
    print_type<decltype(str6)>("auto str6 = arr1");

    // 案例 7：auto&&（万能引用）推导 const 左值数组
    auto&& str7 = arr2;  // arr2 类型为 const char[11]，是左值；auto&& 遇到左值时 auto 推导为 const char(&)[11]，与 && 发生引用折叠后仍为 const char(&)[11]，故 str7 类型为 const char(&)[11]
    print_type<decltype(str7)>("auto str7 = arr2");

    // 案例 8：auto* 推导数组，根据声明形式推导出指针类型
    auto* str8 = arr1;  // arr1 类型为 char[9]，根据 auto* 的声明形式，auto 推导为 char，str8 类型为 char*
    print_type<decltype(str8)>("auto str8 = arr1");

    return 0;
}

#else
int main() {
    return 0;
}
#endif
