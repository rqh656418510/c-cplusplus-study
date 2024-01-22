/*
 * 1. 常用拷贝和替换算法 - copy
 *
 * <p> 将容器内指定范围的元素拷贝到另一个容器中
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    vector<int> vOrigin;

    for (int i = 0; i < 10; i++) {
        vOrigin.push_back(i);
    }

    vector<int> vTarget;

    // 手动分配内存空间
    vTarget.resize(vOrigin.size());

    // 将容器内指定范围的元素拷贝到另一个容器中
    copy(vOrigin.begin(), vOrigin.end(), vTarget.begin());

    // 第一种方式打印
    for_each(vTarget.begin(), vTarget.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 第二种方式打印
    copy(vTarget.begin(), vTarget.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
