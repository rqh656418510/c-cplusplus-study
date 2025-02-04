/**
 * 函数对象
 *
 * <p> 函数指针的使用
 */

#include <iostream>

using namespace std;

template<typename T>
bool my_greater(T a, T b) {
    return a > b;
}

template<typename T>
bool my_less(T a, T b) {
    return a < b;
}

// Compare 是 C++ 的库函数模板
template<typename T, typename Compare>
bool compare(T a, T b, Compare func) {
    // 这里通过函数指针调用函数，是没办法内联的（即使通过 inline 关键字将目标函数声明为内联函数），执行效率较低，因为有函数调用的开销
    return func(a, b);
}

int main() {
    cout << compare(1, 3, my_greater<int>) << endl;
    cout << compare(1, 3, my_less<int>) << endl;
    return 0;
}
