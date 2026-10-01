/**
 * 万能引用universal reference
 *
 * (a) 右值引用的使用
 */

#include <iostream>

// 模板参数 T 只用于返回类型，形参是具体类型的右值引用
template <typename T>
T takeRvalue(int&& x) {
    std::cout << "takeRvalue(int&&) : " << x << std::endl;
    return x;
}

int main() {
    // 传右值，正常调用；右值引用生效（int&& 绑定右值）
    takeRvalue<int>(10);

    int a = 20;

    // 传左值，编译失败：int&& 是右值引用，不能绑定左值；右值引用生效（拒绝左值）
    // takeRvalue<int>(a);

    // 传右值，正常调用；右值引用生效（int&& 绑定右值）
    takeRvalue<int>(25);

    return 0;
}