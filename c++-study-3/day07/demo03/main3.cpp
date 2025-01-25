/**
 * 有序关联容器
 *
 * <p> map 容器的使用
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 有序的键值对容器（键不允许重复）
    map<int, string> map1;

    // 插入键值对
    map1.insert(make_pair(1001, "Tom"));
    map1.insert(make_pair(1002, "Peter"));
    map1.insert(make_pair(1003, "David"));

    // 获取指定键的值，如果 key 不存在，会自动插入一个键值对 [key, string()]
    cout << map1[1002] << endl;

    // 插入或者修改操作
    map1[1004] = "Jim";

    // 获取容器中键值对的数量
    cout << map1.size() << endl;

    // 删除指定的键
    map1.erase(1003);

    // 查找
    auto iterator = map1.find(1001);
    if (iterator != map1.end()) {
        // 获取 key 和 value
        cout << "finded, key: " << iterator->first << ", value: " << iterator->second << endl;
    } else {
        cout << "not finded" << endl;
    }

    // 遍历容器
    for (auto it = map1.begin(); it != map1.end(); ++it) {
        // 获取 key 和 value
        cout << "key: " << it->first << ", value: " << it->second << endl;
    }
    cout << endl;

    return 0;
}
