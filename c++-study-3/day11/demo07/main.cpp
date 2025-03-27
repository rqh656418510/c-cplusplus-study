/**
 * Lambda表达式的应用实践
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    vector<int> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(rand() % 100 + 1);
    }

    // 遍历打印容器
    for_each(vec.begin(), vec.end(), [](int item) -> void { cout << item << " "; });
    cout << endl;

    // 从大到小排序
    sort(vec.begin(), vec.end(), [](int a, int b) -> bool { return a > b; });

    // 遍历打印容器
    for_each(vec.begin(), vec.end(), [](int item) -> void { cout << item << " "; });
    cout << endl;

    // 查找第一个小于 5 的元素
    auto it = find_if(vec.begin(), vec.end(), [](int item) -> bool { return item < 50; });

    // 或者简写
    // auto it = find_if(vec.begin(), vec.end(), [](int item) { return item < 50; });

    if (it != vec.end()) {
        cout << "找到小于 50 的第一个元素：" << *it << endl;
    } else {
        cout << "未找到符合条件的元素" << endl;
    }

    return 0;
}
