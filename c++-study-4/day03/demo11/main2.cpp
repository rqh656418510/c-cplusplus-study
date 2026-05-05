/**
 * using定义别名模板，显式指定模板参数
 *
 * (b) using定义别名模板
 */

#include <iostream>
#include <map>

using namespace std;

// C++ 98 的写法，定义一个 map 类型，key 的类型固定不变，但 value 的类型可以自定义
template <typename st>
struct map_s {
    typedef map<string, st> type;
};

void test01() {
    map_s<int>::type m;
    m.insert({"first", 1});
    m.insert({"second", 2});
}

// C++ 11 的写法（使用别名模板），定义一个 map 类型，key 的类型固定不变，但 value 的类型可以自定义
template <typename T>
using str_map_t = std::map<string, T>;  // str_map_t 是类型别名

void test02() {
    str_map_t<int> m;
    m.insert({"first", 1});
}

int main() {
    test01();
    test02();
    return 0;
}