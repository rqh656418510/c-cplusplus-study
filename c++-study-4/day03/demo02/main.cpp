/**
 * 临时对象深入探讨、解析，提高性能手段
 */

#include <iostream>

int main() {
    int i = 1;
    int&& ref1 = i++;  // i++ 会产生临时变量，ref1 绑定的是临时变量，ref1 和 i 之间没有任何关系
    ref1 += 5;
    std::cout << "i = " << i << ", ref1 = " << ref1 << std::endl;

    return 0;
}