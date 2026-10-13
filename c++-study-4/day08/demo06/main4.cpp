/**
 * 详解decltype含义，decltype主要用途
 *
 * (d) decltype 使用 - 应付可变类型
 */

#ifdef _WIN32

#include <iostream>
#include <vector>

template <typename T>
class MyClass {
public:
    // 使用 decltype 推导 T 的 begin() 函数返回值类型，并将其作为迭代器的类型
    // decltype(T().begin()) 仅用于编译期类型推导，不会实际创建 T 的临时对象，也不会调用 begin() 函数
    // 这里的 T().begin() 是用于描述表达式类型的语法形式，而不是实际执行的函数调用
    decltype(T().begin()) iter;

    void get_begin(T& tmp) {
        iter = tmp.begin();
    }
};

int main() {
    // 定义类型别名 container_type，表示元素类型为 int 的 const std::vector 容器类型（常量容器类型）
    using container_type = const std::vector<int>;

    container_type arr = {1, 2, 3, 4, 5};
    MyClass<container_type> mc;
    mc.get_begin(arr);
    return 0;
}

#else
int main() {
    return 0;
}
#endif
