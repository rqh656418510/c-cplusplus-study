/*
 * 1. C++ 内建的函数对象
 *
 * 1) STL 内建了一些函数对象，分为：算数类函数对象、关系运算类函数对象、逻辑运算类函数对象。
*/

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

void test01() {

    cout << "------ 算数类函数对象的使用 ------" << endl;

    // 取反函数对象
    negate<int> neg;
    cout << neg(10) << endl;

    // 加法函数对象
    plus<int> add;
    cout << add(1, 3) << endl;

}

void test02() {

    cout << "------ 关系运算类函数对象的使用 ------" << endl;

    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(50);
    v.push_back(40);

    // 大于函数对象
    greater<int> greate;

    // 从大到小排序
    sort(v.begin(), v.end(), greate);

    // 遍历打印，使用匿名函数与 Lambda 表达式
    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });
}

int main() {
    test01();
    test02();
    return 0;
}
