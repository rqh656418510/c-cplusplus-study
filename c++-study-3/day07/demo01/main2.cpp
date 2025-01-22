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

    // 容器的默认大小是 0，当插入元素时，容器大小会按照 0 1 2 4 8 16 ... 来扩容
    vector<int> vec;
    cout << "size: " << vec.size() << endl;
    cout << "empty: " << (vec.empty() ? "true" : "false") << endl;

    // 预留空间，只会给容器的底层开辟指定大小的内存空间，并不会添加新的元素，主要用于减少频繁扩容的次数
    vec.reserve(10);
    cout << "size: " << vec.size() << endl;
    cout << "empty: " << (vec.empty() ? "true" : "false") << endl;

    for (int i = 0; i < 10; i++) {
        vec.push_back(rand() % 100 + 1);
    }
    cout << "size: " << vec.size() << endl;
    cout << "empty: " << (vec.empty() ? "true" : "false") << endl;

    cout << "================================" << endl;

    // 容器的默认大小是 0，当插入元素时，容器大小会按照 0 1 2 4 8 16 ... 来扩容
    vector<int> vec2;
    cout << "size: " << vec2.size() << endl;
    cout << "empty: " << (vec2.empty() ? "true" : "false") << endl;

    // 重新指定容器的大小，不仅会给容器的底层开辟指定大小的内存空间，还会填充新的位置
    // 若容器变大，则以默认值（0）填充新位置。如果容器变小，则末尾超出容器大小的元素会被删除
    vec2.resize(10);
    cout << "size: " << vec2.size() << endl;
    cout << "empty: " << (vec2.empty() ? "true" : "false") << endl;

    for (int i = 0; i < 10; i++) {
        vec2.push_back(rand() % 100 + 1);
    }
    cout << "size: " << vec2.size() << endl;
    cout << "empty: " << (vec2.empty() ? "true" : "false") << endl;

    return 0;
}
