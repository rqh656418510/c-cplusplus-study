/*
 * 1. 常用拷贝和替换算法 - replace_if
 *
 * <p> 根据条件将容器内指定范围的旧元素替换为新元素
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 函数对象
class GreaterThenFive {

public:

    // 重载 () 操作符
    bool operator()(const int &value) {
        return value > 5;
    }

};

int main() {
    vector<int> v;

    v.push_back(2);
    v.push_back(2);
    v.push_back(4);
    v.push_back(4);
    v.push_back(6);
    v.push_back(6);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 将大于 5 的元素替换为新元素（基于函数对象）
    replace_if(v.begin(), v.end(), GreaterThenFive(), 8);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    return 0;
}
