/**
 * using定义别名模板，显式指定模板参数
 *
 * (d) 显式指定模板参数
 */

#include <iostream>

using namespace std;

// 定义函数模板
template <typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j) {
    T1 result = i + j;
    return result;
}

int main() {
    // 显式指定模板参数，否则计算结果会出错（由于模板实参类型自动推断，导致整数溢出）
    auto result = sum<double, double, double>(2000000000, 2000000000);
    cout << result << endl;

    return 0;
}