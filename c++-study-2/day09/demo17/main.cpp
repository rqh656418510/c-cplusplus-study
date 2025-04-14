/*
 * 1. 常用算数生成算法 - accumulate
 *
 * <p> 计算容器元素累计总和
*/

#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {

    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);

    // 计算容器元素累计总和
    int sum = accumulate(v.begin(), v.end(), 0);

    cout << "sum = " << sum << endl;

    return 0;
}
