/**
 * 详解decltype含义，decltype主要用途
 *
 * (e) decltype 使用 - 通过变量表达式抽取变量类型
 */

#ifdef _WIN32

#include <boost/type_index.hpp>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int>::size_type size = vec.size();
    std::cout << "size = " << size << std::endl;

    // 案例 1
    // 使用 decltype(vec) 获取变量 vec 的类型 std::vector<int>，再通过 ::size_type 获取其成员类型
    // 等价于 std::vector<int>::size_type size2 = size;
    decltype(vec)::size_type size2 = size;
    std::cout << "size2 = " << size2 << std::endl;

    // 案例 2
    typedef decltype(sizeof(0)) m_size_t;    // 使用 decltype 推导 sizeof(0) 的结果类型，并将其定义为 m_size_t 类型别名
    typedef decltype(sizeof(int)) m_size_t;  // 使用 decltype 推导 sizeof(int) 的结果类型，并将其定义为 m_size_t 类型别名，与上一行等价
    m_size_t num;

    return 0;
}

#else
int main() {
    return 0;
}
#endif
