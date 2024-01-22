/*
 * 1. 常用集合算法 - set_union
 *
 * <p> 求两个集合的并集
 * <p> 注意：两个集合必须是有序序列
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    vector<int> v2;
    v2.push_back(5);
    v2.push_back(7);
    v2.push_back(9);
    v2.push_back(11);

    vector<int> vTarget;
    vTarget.resize(v1.size() + v2.size());

    // 求两个集合的并集
    vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), itEnd, [](int value) { cout << value << " "; });

    return 0;
}
