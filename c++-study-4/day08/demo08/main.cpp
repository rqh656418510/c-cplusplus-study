/**
 * lambda表达式，for_each、find_if简介
 *
 * (a) Lambda 表达式使用
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class CT {
public:
    void process() {
        // [this] 捕获
        auto f1 = [this] { return m_i++; };
        f1();
        std::cout << m_i << std::endl;
    }

private:
    int m_i = 0;
};

// 基础用法
void test01() {
    std::cout << "--------------- test01() ---------------" << std::endl;
    auto f1 = [](const int a, const int b) -> int { return a + b; };
    int r1 = f1(2, 3);
    std::cout << "r1: " << r1 << std::endl;

    auto f2 = []() {};
    auto f3 = [] {};
}

// 捕获方式
void test02() {
    std::cout << "--------------- test02() ---------------" << std::endl;
    int a = 10;
    int b = 20;
    int c = 30;

    // 按值捕获
    auto f1 = [a] { std::cout << "a: " << a << std::endl; };
    f1();

    // 按引用捕获
    auto f2 = [&b] { std::cout << "b: " << b++ << std::endl; };
    f2();
    std::cout << "b = " << b << std::endl;

    // 按引用捕获
    auto f3 = [&] { std::cout << "c: " << c++ << std::endl; };
    f3();
    std::cout << "c = " << c << std::endl;
}

// 直接使用静态局部变量
void test03() {
    std::cout << "--------------- test03() ---------------" << std::endl;
    static int a = 10;
    auto f1 = [] { std::cout << "a: " << a << std::endl; };
    f1();
}

// 捕获 this 指针
void test04() {
    std::cout << "--------------- test04() ---------------" << std::endl;
    CT ct;
    ct.process();
}

// Lambda 表达式存储
void test05() {
    std::cout << "--------------- test05() ---------------" << std::endl;
    std::function<int(int, int)> fun = [](const int x, const int y) -> int { return x + y; };
    const int result = fun(3, 5);
    std::cout << "result: " << result << std::endl; 
}

// 作为标准库算法的谓词
void test06() {
    std::cout << "--------------- test06() ---------------" << std::endl;
    std::vector<int> v{3, 8, 5, 10, 13};

    // 变量容器
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    // 查找元素
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 9; });
    if (it != v.end()) {
        std::cout << *it << std::endl;
    }
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    return 0;
}