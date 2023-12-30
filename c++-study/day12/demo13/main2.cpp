/*
 * 1. 常用的遍历算法 - transform
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 函数对象
class MyTransForm {

public:
    int operator()(int val) {
        return val + 10;
    }

};

int main() {

    // 源容器
    vector<int> vOrigin;
    for (int i = 0; i < 10; i++) {
        vOrigin.push_back(i);
    }

    // 遍历打印（基于匿名函数）
    for_each(vOrigin.begin(), vOrigin.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 目标容器
    vector<int> vTarget;
    // 手动分配内存空间
    vTarget.resize(vOrigin.size());
    // 将指定容器区间元素搬运到另一个容器中
    transform(vOrigin.begin(), vOrigin.end(), vTarget.begin(), MyTransForm());

    // 遍历打印（基于匿名函数）
    for_each(vTarget.begin(), vTarget.end(), [](int value) { cout << value << " "; });

    return 0;
}
