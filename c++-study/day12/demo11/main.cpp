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

    // 第一种方式遍历map集合
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , " << it->second << endl;
    }

    // 第二种方式遍历map集合
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , value = " << it->second << endl;
    }

    cout << "------ map 存取操作 ------" << endl;

    // 获取指定的Key
    map<int, int>::iterator item = m.find(5);
    cout << "key = " << item->first << " , value = " << item->second << endl;

    // 第一种方式判断Key是否存在
    // 如果Key存在，find()函数会返回Key对应的迭代器，如果Key不存在，find()函数会返回尾后迭代器end()
    if (m.find(100) == m.end()) {
        cout << "key " << 100 << " not exist" << endl;
    }

    // 第二种方式判断Key是否存在
    // count()函数用于统计Key值在Map中出现的次数，Map的Key是不允许重复的，因此如果Key存在会返回1，不存在会返回0
    if (m.count(5) == 1) {
        cout << "key " << 5 << " existed" << endl;
    }

    cout << "------ map 删除操作 ------" << endl;

    // 删除指定的Key
    m.erase(7);
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << " , value = " << it->second << endl;
    }

}