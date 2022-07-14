/*
 * 1. deque容器的常用操作
*/

#include <iostream>
#include <deque>

using namespace std;

void printDeque(const deque<int> &d) {
    // 遍历容器
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    cout << "------ deque 大小操作 ------" << endl;

    deque<int> d1;
    d1.assign(5, 10);
    printDeque(d1);

    // 判断容器是否为空
    bool empty = d1.empty();
    cout << (empty ? "yes" : "no") << endl;

    // 获取容器中元素的个数
    size_t size = d1.size();
    cout << size << endl;

    // 重新指定容器的大小为 num，若容器变大，则以默认值（0）填充新位置。如果容器变小，则末尾超出容器大小的元素会被删除
    d1.resize(7);
    printDeque(d1);

    // 重新指定容器的大小为 num，若容器变大，则以指定值填充新位置。如果容器变小，则末尾超出容器大小的元素会被删除
    d1.resize(10, 8);
    printDeque(d1);

    cout << "------ deque 读取操作 ------" << endl;

    deque<int> d2;
    d2.push_back(1);
    d2.push_back(2);
    d2.push_back(3);
    d2.push_back(4);
    d2.push_back(5);

    // 返回索引所指向的数据，如果索引越界，抛出 out_of_range 异常
    int num1 = d2.at(2);
    cout << "num1 = " << num1 << endl;

    // 返回索引所指向的数据，如果索引越界，程序终止运行
    int num2 = d2[3];
    cout << "num2 = " << num2 << endl;

    // 返回容器中第一个数据元素
    int font = d2.front();
    cout << "font = " << font << endl;

    // 返回容器中最后一个数据元素
    int back = d2.back();
    cout << "back = " << back << endl;

    cout << "------ deque 插入操作 ------" << endl;

    deque<int> d3(3, 8);
    printDeque(d3);

    // 往迭代器指向的位置插入指定的元素
    d3.insert(d3.begin(), 10);
    printDeque(d3);

    // 往迭代器指向的位置插入 n 个指定的元素
    d3.insert(d3.begin(), 2, 11);
    printDeque(d3);

    // 往迭代器指向的位置插入 [begin, end) 区间的数据
    deque<int> d4(2, 12);
    d3.insert(d3.begin(), d4.begin(), d4.end());
    printDeque(d3);

    // 在容器头部插入一个数据
    d4.push_front(13);
    printDeque(d4);

    // 在容器尾部添加一个数据
    d4.push_back(11);
    printDeque(d4);

    cout << "------ deque 删除操作 ------" << endl;

    deque<int> d5;
    d5.push_back(1);
    d5.push_back(2);
    d5.push_back(3);
    d5.push_back(4);
    d5.push_back(5);
    d5.push_back(6);

    // 删除指定位置的数据，会返回下一个数据的位置
    d5.erase(d5.begin());
    printDeque(d5);

    // 删除容器第一个数据
    d5.pop_front();
    printDeque(d5);

    // 删除容器最后一个数据
    d5.pop_back();
    printDeque(d5);

    // 清空容器的所有数据
    d5.clear();

    return 0;
}