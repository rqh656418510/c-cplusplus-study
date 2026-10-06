/**
 * 理解模板类型推断、查看类型推断结果
 *
 * (b) 指针类型
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void func(const T* val) {
    std::cout << "---------------begin---------------" << std::endl;
    using boost::typeindex::type_id_with_cvr;
    // 查看模板参数 T 的类型推断结果
    std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // 查看形参 val 的类型推断结果
    std::cout << "val = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
    std::cout << "---------------end---------------" << std::endl;
}

template <typename T>
void func2(T* val) {
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
    const int* d = &a;

    func(&a);
    func(&b);
    func(d);
    std::cout << "*********************************\n" << std::endl;

    func2(&a);
    func2(&b);
    func2(d);
    std::cout << "*********************************\n" << std::endl;

    return 0;
}

#else
int main() {
    return 0;
}
#endif
