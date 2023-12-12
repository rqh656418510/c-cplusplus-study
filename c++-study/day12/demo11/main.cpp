/*
 * 1. map / multimap 容器的使用
*/

#include <iostream>
#include <map>

using namespace std;

int main() {

    cout << "------ map 插入操作 ------" << endl;

    // 默认构造函数
    map<int, int> m;

    // 第一种数据插入方式
    m.insert(pair<int, int>(1, 2));
    // 第二种数据插入方式（推荐）
    m.insert(make_pair(3, 4));
    // 第三种数据插入方式
    m.insert(map<int, int>::value_type(5, 6));
    // 第四种数据插入方式
    m[7] = 8;

    cout << "------ map 遍历操作 ------" << endl;

    // 第一种方式遍历 map 集合
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , " << it->second << endl;
    }

    // 第二种方式遍历 map 集合
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , value = " << it->second << endl;
    }

    cout << "------ map 存取操作 ------" << endl;

    // 获取指定的 key
    map<int, int>::iterator item = m.find(5);
    cout << "key = " << item->first << " , value = " << item->second << endl;

    // 第一种方式判断 key 是否存在
    // 如果 key 存在，find() 函数会返回 key 对应的迭代器，如果 key 不存在，find() 函数会返回尾后迭代器 end()
    if (m.find(100) == m.end()) {
        cout << "key " << 100 << " not exist" << endl;
    }

    // 第二种方式判断 key 是否存在
    // count() 函数用于统计 key 值在 map 中出现的次数，map 的 key 是不允许重复的，因此如果 key 存在会返回 1，不存在会返回 0
    if (m.count(5) == 1) {
        cout << "key " << 5 << " existed" << endl;
    }

    // 返回第一个 key >= keyElem 元素的迭代器
    map<int, int>::iterator result1 = m.lower_bound(3);
    if (result1 != m.end()) {
        cout << "found result for lower_bound(3), key: " << result1->first << ", value: " << result1->second << endl;
    } else {
        cout << "not found result for lower_bound(3)";
    }

    // 返回第一个 key > keyElem 元素的迭代器
    map<int, int>::iterator result2 = m.upper_bound(3);
    if (result2 != m.end()) {
        cout << "found result for upper_bound(3), key: " << result2->first << ", value: " << result2->second << endl;
    } else {
        cout << "not found result for upper_bound(3)";
    }

    cout << "------ map 删除操作 ------" << endl;

    // 删除指定的 key
    m.erase(7);
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , value = " << it->second << endl;
    }

}