/*
 * 1. 函数对象的谓词
 *
 * 1) 一元函数对象：函数参数有 1 个
 * 2) 二元函数对象：函数参数有 2 个
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 一元函数对象
class GreaterThen20 {

public:

    // 重载 () 操作符，有一个参数
    bool operator()(const int &val) {
        return val > 20;
    }

};

// 二元函数对象
class MyCompare {

public:

    // 重载 () 操作符，有两个参数
    bool operator()(const int &v1, const int &v2) {
        return v1 > v2;
    }

};

void test01() {
    cout << "------ 一元函数对象的使用 ------" << endl;

    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    // 初始化一元函数对象
    GreaterThen20 greaterThen;

    // 查找第一个大于 20 的元素
    vector<int>::iterator pos = find_if(v.begin(), v.end(), greaterThen);

    if (pos != v.end()) {
        cout << "first number greater then 20 is " << *pos << endl;
    } else {
        cout << "not found first number greater then 20" << endl;
    }

}

void test02() {
    cout << "------ 二元函数对象的使用 ------" << endl;

    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(50);
    v.push_back(40);

    // 初始化二元函数对象
    MyCompare myCompare;

    // 根据自定义规则进行排序
    sort(v.begin(), v.end(), myCompare);

    // 遍历打印，使用匿名函数与 Lambda 表达式
    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

}

int main() {
    test01();
    test02();
    return 0;
}