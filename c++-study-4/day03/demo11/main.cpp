/**
 * using定义别名模板，显式指定模板参数
 *
 * (a) using定义类型别名
 */

#include <iostream>
#include <map>

using namespace std;

// 使用 typedef 定义类型别名
void test01() {
    typedef unsigned int uint_t;
    uint_t a;

    typedef map<string, int> map_s_i;
    map_s_i m;
    m.insert({"first", 1});
    m.insert({"second", 2});

    typedef map<string, string> map_s_s;
    map_s_s m2;
    m2.insert({"first", "one"});
    m2.insert({"second", "two"});
}

// 使用 using 定义类型别名
void test02() {
    using uint_t = unsigned int;
    uint_t a;

    using map_s_i = map<string, int>;
    map_s_i m;
    m.insert({"first", 1});
    m.insert({"second", 2});

    using map_s_s = map<string, string>;
    map_s_s m2;
    m2.insert({"first", "one"});
    m2.insert({"second", "two"});
}

int main() {
    test01();
    test02();
    return 0;
}