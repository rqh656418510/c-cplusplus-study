/*
 * 1. 容器初识（容器的嵌套使用）
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 定义容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<vector<int>> v;

    // 插入数据
    for (int i = 0; i < 5; i++) {
        v1.push_back(i + 1);
        v2.push_back(i + 6);
        v3.push_back(i + 11);
    }
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    // 遍历容器
    for (vector<vector<int>>::iterator it1 = v.begin(); it1 != v.end(); it1++) {
        for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}