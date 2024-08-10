/**
 * 类型转换-重新解释类型
 */
#include <iostream>

using namespace std;

void test01() {
    int a = 10;
    // 将整数强制转换成指针
    int *p = reinterpret_cast<int *>(a);
}

int main() {
    test01();
    return 0;
}
