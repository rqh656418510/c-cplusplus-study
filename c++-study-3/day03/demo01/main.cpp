/**
 * 理解函数模板
 */

#include <iostream>
#include <cstring>

using namespace std;

// 定义一个模板参数列表
template<typename T>
// 定义一个函数模板
bool compare(T a, T b) {
    cout << "call compare(T a, T b)" << endl;
    return a > b;
}

// 针对 compare 函数模板，提供 const char* 类型的特例化版本
template<>
bool compare<const char *>(const char *a, const char *b) {
    cout << "call compare(const char *a, const char *b)" << endl;
    return strcmp(a, b);
}

// 普通函数（非模板函数）
bool compare(const char *a, const char *b) {
    cout << "call normal compare()" << endl;
    return strcmp(a, b);
}

/**
在函数调用点，编译器会使用用户指定的类型，从原函数模板实例化一份函数代码出来（称为模板函数）

bool compare<int> (int a, int b) {

}

bool compare<double> (double a, double b) {

}
*/

int main() {
    // 函数的调用点
    compare<int>(10, 30);
    compare<double>(1.3, 4.5);

    // 函数模板的实参推演
    compare(20, 40);

    // 编译器优先将 compare 处理成普通函数，如果函数不存在，才会去找 compare 模板函数
    compare("abc", "efg");
    compare<const char *>("abc", "efg");

    return 0;
}