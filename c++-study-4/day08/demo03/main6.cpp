/**
 * 理解模板类型推断、查看类型推断结果
 *
 * (f) 函数名做实参
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void func(T val) {
    std::cout << "---------------begin---------------" << std::endl;
    using boost::typeindex::type_id_with_cvr;
    // 查看模板参数 T 的类型推断结果
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // 查看形参 val 的类型推断结果
    std::cout << "val = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
    std::cout << "---------------end---------------" << std::endl;
}

template <typename T>
void func2(T& val) {
    std::cout << "---------------begin---------------" << std::endl;
    using boost::typeindex::type_id_with_cvr;
    // 查看模板参数 T 的类型推断结果
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // 查看形参 val 的类型推断结果
    std::cout << "val = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
    std::cout << "---------------end---------------" << std::endl;
}

void process() {
    std::cout << "process()" << std::endl;
}

int main() {
    func(process);   // 实参传递函数名称
    func2(process);  // 实参传递函数名称
    return 0;
}

#else
int main() {
    return 0;
}
#endif
