/**
 * 万能引用universal reference
 *
 * (b) 万能引用的使用
 */

#include <iostream>

// 模板参数 T 参与形参推导，形参 T&& 是万能引用
template <typename T>
T takeRvalue(T&& x) {
    std::cout << "takeRvalue(T&&) : " << x << std::endl;
    return x;
}

int main() {
    // 显式指定 T=int，形参为 int&&，绑定右值；万能引用未生效（表现为普通右值引用）
    takeRvalue<int>(10);

    int a = 20;

    // 显式指定 T=int，形参是 int&&，左值 a 不能绑定到 int&&，会编译失败；也就是说，显式指定 T 后它表现得像普通右值引用，万能引用未生效
    // takeRvalue<int>(a);

    // 显式指定 T=int&，形参折叠为 int&，绑定左值；万能引用未生效（表现为普通左值引用）
    takeRvalue<int&>(a);

    // 不显式指定 T，编译器会将 T 推导为 int&，绑定左值；万能引用生效
    takeRvalue(a);

    // 不显式指定 T，编译器会将 T 推导为 int，绑定右值；万能引用生效
    takeRvalue(25);

    return 0;
}
