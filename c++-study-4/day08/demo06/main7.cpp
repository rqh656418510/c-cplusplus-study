/**
 * 详解decltype含义，decltype主要用途
 *
 * (g) decltype 使用 - auto 结合 decltype 构成函数返回类型后置语法
 */

#include <iostream>

// 重载函数一
int &tf(int &i) {
    std::cout << "int &tf(int &i)" << std::endl;
    return i;
}

// 重载函数二
double tf(double &d) {
    std::cout << "double tf(double &d)" << std::endl;
    return d;
}

template <typename T>
auto Func(T &t) -> decltype(tf(t)) {  // 使用函数返回类型后置语法，根据 tf(t) 的表达式类型推导 Func 的返回类型
    return tf(t);                     // 调用与参数类型匹配的 tf() 重载函数，并返回结果
}

int main() {
    int i = 10;
    Func(i);  // T 推导为 int，decltype(tf(t)) 推导为 int&

    double j = 20.5f;
    Func(j);  // T 推导为 double，decltype(tf(t)) 推导为 double

    return 0;
}