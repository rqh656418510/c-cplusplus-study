/*
 * 1. 常用的查找算法 - count_if
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 普通函数
bool MyGreaterThenFive(const int &v) {
    return v > 5;
}

// 函数对象
class GreaterThenFiveFunctor {

public:
    bool operator()(const int &v) {
        return v > 5;
    }

};

int main() {
    vector<int> v;

    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    // 根据条件统计元素出现次数（基于普通函数）
    int total = count_if(v.begin(), v.end(), MyGreaterThenFive);
    cout << "total: " << total << endl;

    // 根据条件统计元素出现次数（基于函数对象）
    int count = count_if(v.begin(), v.end(), GreaterThenFiveFunctor());
    cout << "count: " << total << endl;

    return 0;
}
