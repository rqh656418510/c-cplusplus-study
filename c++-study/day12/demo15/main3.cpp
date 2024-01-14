/*
 * 1. 常用的排序算法 - random_shuffle
 *
 * <p> 对指定范围内的元素随机调整顺序
*/

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main() {

    // 初始化随机种子
    srand((unsigned int) time(NULL));

    vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 对指定范围内的元素随机调整顺序（洗牌）
    random_shuffle(v.begin(), v.end());

    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    return 0;
}
