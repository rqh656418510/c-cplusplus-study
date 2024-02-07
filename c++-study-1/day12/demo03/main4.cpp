/*
 * 1. vector 容器预留空间
*/

#include <iostream>
#include <vector>

using namespace std;

void initData(vector<int> &v, size_t size, bool reserve) {
    // 预留空间
    if (reserve) {
        v.reserve(size);
    }

    int count = 0;
    int *pStart = NULL;
    for (int i = 0; i < size; i++) {
        // 插入容器数据
        v.push_back(i);
        // 统计容器改变容量的次数
        if (pStart != &v[0]) {
            pStart = &v[0];
            count++;
        }
    }
    cout << "count : " << count << endl;
}

int main() {
    // 不申请预览空间
    vector<int> v1;
    initData(v1, 100000, false);

    // 申请预览空间
    vector<int> v2;
    initData(v2, 100000, true);

    return 0;
}