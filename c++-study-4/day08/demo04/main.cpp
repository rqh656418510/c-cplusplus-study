/**
 * 引用折叠，转发、完美转发，forward
 *
 * (a) 引用折叠
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void func(T&& val) {
    std::cout << "---------------begin---------------" << std::endl;
    using boost::typeindex::type_id_with_cvr;
    // 查看模板参数 T 的类型推断结果
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // 查看形参 val 的类型推断结果
    std::cout << "val = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
    std::cout << "---------------end---------------" << std::endl;
}

int main() {
    int a = 150;
    func(a);    // 实参传递值（左值），会发生引用折叠，模板参数 T 推导为 int& 类型，形参 val 推导为 int& 类型（左值引用）
    func(100);  // 实参传递值（右值），不会发生引用折叠，模板参数 T 推导为 int 类型，形参 val 推导为 int&& 类型（右值引用）
    return 0;
}

#else
int main() {
    return 0;
}
#endif
