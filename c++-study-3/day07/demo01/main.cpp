/**
 * vector容器
 *
 * <p> vector 底层的数据结构是动态开辟的数组，每次会以原来空间大小的 2 倍进行扩容
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    vector<int> vec;

    for (int i = 0; i < 10; i++) {
        // 往容器尾部插入元素
        vec.push_back(random() % 100 + 1);
    }

    // 获取容器中元素数量
    cout << "size: " << vec.size() << endl;

    // 迭代器遍历容器
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 基于下标访问元素
    cout << "vec[3] = " << vec[3] << endl;

    cout << "================================" << endl;

    // 将容器中所有的偶数元素全部删除
    for (vector<int>::iterator it = vec.begin(); it != vec.end();) {
        if (*it % 2 == 0) {
            // 连续删除元素后必须更新迭代器，否则迭代器会失效
            it = vec.erase(it);
        } else {
            ++it;
        }
    }

    // 循环遍历容器
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "================================" << endl;

    // 往容器中所有的奇数元素前面都添加一个偶数
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        if (*it % 2 != 0) {
            // 连续插入元素后必须更新迭代器，否则迭代器会失效
            it = vec.insert(it, *it - 1);
            ++it;
        }
    }

    // 循环遍历容器
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
