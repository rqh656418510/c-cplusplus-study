/*
 * 1. 常用的排序算法 - sort
*/

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

bool MyCompare(int v1, int v2) {
    return v1 > v2;
}

void test01() {
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(5);
    v1.push_back(8);
    v1.push_back(7);
    v1.push_back(9);

    // 默认从小到大排序
    sort(v1.begin(), v1.end());

    for_each(v1.begin(), v1.end(), [](int value) { cout << value << " "; });

    cout << endl;
}

void test02() {
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(5);
    v1.push_back(8);
    v1.push_back(7);
    v1.push_back(9);

    // 从大到小排序（基于普通函数）
    sort(v1.begin(), v1.end(), MyCompare);

    for_each(v1.begin(), v1.end(), [](int value) { cout << value << " "; });

    cout << endl;
}

void test03() {
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(5);
    v1.push_back(8);
    v1.push_back(7);
    v1.push_back(9);

    // 从大到小排序（基于函数对象）
    sort(v1.begin(), v1.end(), greater<int>());

    for_each(v1.begin(), v1.end(), [](int value) { cout << value << " "; });

    cout << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
