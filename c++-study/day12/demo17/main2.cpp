/*
 * 1. 常用算数生成算法 - fill
 *
 * <p> 向容器中填充元素
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> v;
    v.resize(5);

    // 向容器中填充元素
    fill(v.begin(), v.end(), 6);

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    return 0;
}
