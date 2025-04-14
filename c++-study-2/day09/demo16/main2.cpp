/*
 * 1. 常用拷贝和替换算法 - replace
 *
 * <p> 将容器内指定范围的旧元素替换为新元素
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v;

    v.push_back(1);
    v.push_back(1);
    v.push_back(3);
    v.push_back(3);
    v.push_back(5);
    v.push_back(5);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 将容器内指定范围的旧元素替换为新元素
    replace(v.begin(), v.end(), 3, 8);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    return 0;
}
