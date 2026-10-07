/**
 * 引用折叠，转发、完美转发，forward
 *
 * (b) 转发、完美转发
 */

#include <iostream>

// 函数模板，第二个参数使用万能引用
template <typename F, typename T1, typename T2>
void process(F f, T1&& t1, T2 t2) {
    // f 是要调用的第三方函数，也就是要转发到的目标函数
    f(t1, t2);
}

void func(int& i, int j) {
    ++i;  // 改变 i 的值
    std::cout << i + j << std::endl;
}

int main() {
    int a = 10;
    process(func, a, 30);         // 通过 process() 间接调用 func() 函数
    std::cout << a << std::endl;  // 注意，变量 a 的值会发生改变
    return 0;
}