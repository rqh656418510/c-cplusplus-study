/**
 * 嵌入式指针概念及范例、内存池改进版
 *
 * (a) 嵌入指针使用
 */

#include <iostream>

class MyTest {
public:
    struct FreeBlock {
        struct FreeBlock *next;  // 嵌入式指针（64 位环境下，一个指针本身占用 8 个字节）
    };

private:
    int m_i;
    int m_j;
    int m_k;
};

int main() {
    MyTest mytest;
    std::cout << sizeof(mytest) << std::endl;  // 输出 12

    MyTest::FreeBlock *ptemp;
    ptemp = reinterpret_cast<MyTest::FreeBlock *>(&mytest);  // 将 mytest 对象的首地址给了 ptemp 指针，这个 ptemp 指针就指向了 mytest 对象的首地址

    std::cout << sizeof(MyTest::FreeBlock) << std::endl;  // 输出 8
    std::cout << sizeof(ptemp->next) << std::endl;        // 输出 8
    ptemp->next = nullptr;

    return 0;
}