/*
 * 1. 容器初识（存放基础数据类型）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void m_print(const int num) {
    cout << num << " ";
}

int main() {
    // 定义容器
    vector<int> v;

    // 插入数据
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    v.push_back(15);

    // 第一种方式：遍历容器
    vector<int>::iterator itBegin = v.begin();
    vector<int>::iterator itEnd = v.end();
    while (itBegin != itEnd) {
        cout << *(itBegin++) << " ";
    }
    cout << endl;

    // 第二种方式：遍历容器
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 第三种方式：遍历容器
    for_each(v.begin(), v.end(), m_print);

    return 0;
}