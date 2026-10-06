/**
 * 理解模板类型推断、查看类型推断结果
 *
 * (a) 引用类型
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void func(T& val) {
    std::cout << "---------------begin---------------" << std::endl;
    using boost::typeindex::type_id_with_cvr;
    // 查看模板参数 T 的类型推断结果
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // 查看形参 val 的类型推断结果
    std::cout << "val = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
    std::cout << "---------------end---------------" << std::endl;
}

template <typename T>
void func2(const T& val) {
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
    const int b = a;
    const int& c = a;

    func(a);  // 实参传递值
    func(b);  // 实参传递常量对象
    func(c);  // 实参传递常量引用
    std::cout << "*********************************\n" << std::endl;

    func2(100);  // 实参传递值
    func2(a);    // 实参传递值
    func2(b);    // 实参传递常量对象
    func2(c);    // 实参传递常量引用
    std::cout << "*********************************\n" << std::endl;

    return 0;
}

#else
int main() {
    return 0;
}
#endif
