/*
 * 1. vector 容器收缩空间
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1;

    // 插入容器数据
    for (int i = 0; i < 100000; i++) {
        v1.push_back(i);
    }

    cout << "size = " << v1.size() << endl;
    cout << "capacity = " << v1.capacity() << endl;

    // 重新指定容器的大小，此时容器的容量不会改变
    v1.resize(5);
    cout << "size = " << v1.size() << endl;
    cout << "capacity = " << v1.capacity() << endl;

    // 巧用匿名对象和 swap() 函数收缩 vector 容器的空间
    vector<int>(v1).swap(v1);
    cout << "size = " << v1.size() << endl;
    cout << "capacity = " << v1.capacity() << endl;

    return 0;
}