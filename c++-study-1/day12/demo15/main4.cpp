/*
 * 1. 常用的排序算法 - reverse
 *
 * <p> 反转指定范围元素的位置
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> v;
    v.push_back(10);
    v.push_back(5);
    v.push_back(8);
    v.push_back(7);
    v.push_back(9);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 反转指定范围元素的位置
    reverse(v.begin(), v.end());

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    return 0;
}
