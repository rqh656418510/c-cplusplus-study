/*
 * 1. vector 容器逆序遍历
*/

#include<iostream>
#include<vector>

using namespace std;

int main() {
    vector<int> v1;
    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
    }

    // 顺序遍历容器
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
        cout << *it << " ";
    }

    cout << endl;

    // 逆序遍历容器（使用逆序迭代器）
    for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++) {
        cout << *it << " ";
    }

    cout << endl;

    // vector 的迭代器是随机访问迭代器，支持跳跃式访问
    vector<int>::iterator itBegin = v1.begin();
    itBegin = itBegin + 2;
    cout << *itBegin << endl;

    return 0;
}