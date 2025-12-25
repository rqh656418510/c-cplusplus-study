/**
 * vector类型介绍
 */

#include <iostream>
#include <vector>

using namespace std;

// vector 初始化方式
void test0() {
    // 1. 默认初始化方式，创建一个空的 vector 对象
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    // 2. 元素拷贝的初始化方式
    vector<int> v2(v1);
    vector<int> v3 = v1;

    // 3. 列表初始化方式
    vector<int> v4 = {1, 2, 3, 4};
    vector<int> v5{1, 2, 3, 4};

    // 4. 创建指定数量的元素
    vector<int> v6(5);           // 指定大小（元素值默认初始化），结果：[0, 0, 0, 0, 0]
    std::vector<int> v7(5, 10);  // 指定大小 + 指定初始值，结果：[10, 10, 10, 10, 10]
}

// vector 与范围 for 使用
void test1() {
    vector<string> v1 = {"a", "b", "c"};

    // 通过范围 for 和引用遍历 vector 所有元素，使用常量引用
    for (const string& item : v1) {
        cout << item << " ";
    }
    cout << endl;

    // 通过范围 for 和引用遍历 vector 所有元素，并更改其元素的值，使用普通引用
    for (string& item : v1) {
        item = item + "1";
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    test0();
    test1();
    return 0;
}