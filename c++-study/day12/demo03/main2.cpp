/*
 * 1. vector容器的常用操作
*/

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> &v) {
    // 遍历vector
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    vector<int> v1;
    v1.assign(5, 10);

    cout << "------ vector 大小、容量操作 ------" << endl;

    // 获取容器中元素的个数
    size_t size = v1.size();
    cout << "size = " << size << endl;

    // 判断容器是否为空
    bool empty = v1.empty();
    cout << (empty == 0 ? "true" : "false") << endl;

    // 重新指定容器的大小为 num，若容器变大，则以默认值（0）填充新位置。如果容器变小，则末尾超出容器大小的元素会被删除
    v1.resize(7);
    printVector(v1);

    // 重新指定容器的大小为 num，若容器变大，则以指定值填充新位置。如果容器变小，则末尾超出容器大小的元素会被删除
    v1.resize(10, 8);
    printVector(v1);

    // 获取容器的容量
    size_t capacity = v1.capacity();
    cout << "capacity = " << capacity << endl;

    cout << "------ vector 数据读取操作 ------" << endl;

    vector<int> v2;
    v2.push_back(3);
    v2.push_back(6);
    v2.push_back(9);
    v2.push_back(12);
    v2.push_back(15);

    // 返回索引所指向的数据，如果索引越界，抛出 out_of_range 异常
    int num1 = v2.at(1);
    cout << "num1 = " << num1 << endl;

    // 返回索引所指向的数据，如果索引越界，程序终止运行
    int num2 = v2[3];
    cout << "num2 = " << num2 << endl;

    // 返回容器中第一个数据元素
    int font = v2.front();
    cout << "font = " << font << endl;

    // 返回容器中最后一个数据元素
    int back = v2.back();
    cout << "back = " << back << endl;

    cout << "------ vector 插入和删除操作 ------" << endl;

    // 往迭代器指向的位置插入 n 个指定的元素，其中元素个数可以省略
    vector<int> v3(5, 8);
    v3.insert(v3.begin(), 2, 10);
    printVector(v3);

    // 往容器的尾部插入元素
    v3.push_back(11);
    printVector(v3);

    // 删除最后一个元素
    v3.pop_back();
    printVector(v3);

    // 删除迭代器指向的元素，迭代器就是指针
    v3.erase(v3.begin());
    printVector(v3);

    // 删除迭代器从 start 到 end 之间的元素
    v3.erase(v3.begin(), v3.end());
    if (v3.empty()) {
        cout << "vector is empty" << endl;
    }

    // 删除容器中的所有元素
    v3.clear();

    return 0;
}