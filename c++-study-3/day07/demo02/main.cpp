/**
 * 无序关联容器
 *
 * <p> unordered_set 容器的使用
 */

#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 存储唯一键值（不允许重复）的无序容器
    unordered_set<int> set1;

    // 插入元素
    for (int i = 0; i < 50; i++) {
        set1.insert(random() % 20 + 1);
    }

    // 遍历容器
    for (auto it = set1.begin(); it != set1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 获取容器中的元素数量
    cout << set1.size() << endl;

    // 统计容器中元素是 5 的个数
    cout << set1.count(5) << endl;

    // 删除元素
    set1.erase(20);

    // 查找元素
    auto iterator = set1.find(15);
    if (iterator != set1.end()) {
        cout << "find item : " << *iterator << endl;
    } else {
        cout << "not find item" << endl;
    }

    // 循环遍历
    for (int i: set1) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

