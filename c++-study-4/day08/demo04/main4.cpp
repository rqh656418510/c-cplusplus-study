/**
 * 引用折叠，转发、完美转发，forward
 *
 * (d) std::forward 实现完美转发
 */

#include <iostream>

// 重载函数一（参数是左值引用）
void printInfo(int& val) {
    std::cout << "printInfo(int&)" << std::endl;
}

// 重载函数二（参数是右值引用）
void printInfo(int&& val) {
    std::cout << "printInfo(int&&)" << std::endl;
}

// 函数模板，第二个参数使用万能引用
template <typename T>
void process(T&& t) {
    std::cout << "---------------begin---------------" << std::endl;
    printInfo(t);                   // 表达式 t 在函数体内永远是左值
    printInfo(std::forward<T>(t));  // 完美转发，恢复参数原有的值类别（左值或右值）
    printInfo(std::move(t));        // 不管原来是什么值类别（左值或右值），强制转换为右值
    std::cout << "---------------end---------------" << std::endl;
}

int main() {
    int a = 5;
    process(a);  // 实参传递左值

    process(10);  // 实参传递右值

    return 0;
}