/*
 * 1. 常用拷贝和替换算法 - swap
 *
 * <p> 互换两个容器的元素
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v1;
    v1.push_back(12);
    v1.push_back(12);
    v1.push_back(14);
    v1.push_back(14);
    v1.push_back(16);
    v1.push_back(16);


    vector<int> v2;
    v2.push_back(32);
    v2.push_back(32);
    v2.push_back(34);
    v2.push_back(34);

    cout << endl << "----------- before swap -------------" << endl;

    for_each(v1.begin(), v1.end(), [](int value) { cout << value << " "; });
    cout << endl;
    for_each(v2.begin(), v2.end(), [](int value) { cout << value << " "; });

    // 互换两个容器的元素
    swap(v1, v2);

    cout << endl << "----------- after swap -------------" << endl;

    for_each(v1.begin(), v1.end(), [](int value) { cout << value << " "; });
    cout << endl;
    for_each(v2.begin(), v2.end(), [](int value) { cout << value << " "; });

    return 0;
}
