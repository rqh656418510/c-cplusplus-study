/*
 * 1. 常用的排序算法 - merge
 *
 * <p> 将两个容器元素合并，并存储到另一个容器中
 * <p> 注意：合并的两个容器必须是有序的
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v1;
    vector<int> v2;

    for (int i = 1; i <= 5; i++) {
        v1.push_back(i);
        v2.push_back(i * 10);
    }

    vector<int> vTarget;
    vTarget.resize(v1.size() + v2.size());

    // 将两个容器元素合并，并存储到另一个容
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), vTarget.end(), [](int value) { cout << value << " "; });

    return 0;
}
