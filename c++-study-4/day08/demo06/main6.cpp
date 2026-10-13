/**
 * 详解decltype含义，decltype主要用途
 *
 * (f) decltype 使用 - decltype(auto) 的使用方式，C++ 14 开始支持
 */

#include <iostream>

#if __cplusplus > 201103L
template <typename T>
decltype(auto) process(T& v) {  // 使用 decltype(auto) 根据返回表达式推导返回类型，保留引用等类型属性
    v *= 2;
    return v;  // v 是具名变量表达式，属于左值，因此返回类型为 T&
}

int main() {
    int a = 100;
    process(a) = 20;  // process(a) 返回 int& 时，可以直接修改变量 a；若将上面的 decltype(auto) 改为 auto，则返回类型为 int，函数调用结果是纯右值，不能作为赋值运算符的左操作数，因此编译失败
    std::cout << a << std::endl;  // 输出 20

    return 0;
}
#else
int main() {
    return 0;
}
#endif
