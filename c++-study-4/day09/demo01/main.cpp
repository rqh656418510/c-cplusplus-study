/**
 * 类对象所占用的空间
 * 
 * (a) 空类对象
 */

#include <iostream>

// 空类
class A {

};

int main() {
    A a;
    int size = sizeof(a);
    std::cout << "size = " << size << std::endl;  // 输出 size = 1
    return 0;
}