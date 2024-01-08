/*
 * 1. 常用的查找算法 - adjacent_find
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v;

    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(5);
    v.push_back(6);
    v.push_back(2);

    // adjacent_find 查找相邻重复元素，返回相邻元素的第一个位置的迭代器
    vector<int>::iterator pos = adjacent_find(v.begin(), v.end());
    if (pos != v.end()) {
        cout << *pos << ", " << *pos++ << endl;
    } else {
        cout << "not found element" << endl;
    }

    return 0;
}
