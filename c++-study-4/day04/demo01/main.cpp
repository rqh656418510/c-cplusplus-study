/**
 * 直接内存管理(new-delete)、观察内存泄漏
 *
 * (a) 直接内存管理(new-delete)
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MyClass {
public:
    int m_i;
};

// 自动内存管理
void func() {
    int a = 0;          // 局部变量（临时）
    MyClass mc;         // 局部变量（临时）
    static int b = 30;  // 静态局部变量（全局）
}

// 直接内存管理
int main() {
    // 初值未定义
    int* pint = new int;
    delete pint;

    // 初值为0，空括号()表示值初始化
    int* pint2 = new int();
    delete pint2;

    // 初值为10
    int* pint3 = new int(10);
    delete pint3;

    // 初值是空字符串，调用string的默认构造函数
    string* pstr = new string;
    delete pstr;

    // 调用string的默认构造函数，空括号()表示值初始化
    string* pstr2 = new string();
    delete pstr2;

    // 初值为AAAAA
    string* pstr3 = new string(5, 'A');

    // auto 配合 new 使用，pstr4 推断的类型是 string **
    auto pstr4 = new auto(pstr3);
    delete pstr3;
    delete pstr4;

    // 初始值为 1, 2, 3
    vector<int>* pvec = new vector<int>{1, 2, 3};
    delete pvec;

    // 调用MyClass的默认构造函数
    MyClass* pmc = new MyClass;
    delete pmc;

    // 调用MyClass的默认构造函数，空括号()表示值初始化
    MyClass* pmc2 = new MyClass();
    delete pmc2;

    // 动态分配const对象
    const int* pconst = new const int(100);
    delete pconst;

    return 0;
}