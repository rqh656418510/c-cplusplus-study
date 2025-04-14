/*
 * 1. 常用的遍历算法 - transform
 *
 * transform 算法用于将指定容器区间元素搬运到另一个容器中
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 函数对象
class MyTransForm {

public:
    int operator()(int val) {
        return val + 10;
    }

};

// 第一种使用方法
void test01() {
    cout << "----------- transform 的第一种用法 -------------" << endl;

    // 源容器
    vector<int> vOrigin;
    for (int i = 0; i < 10; i++) {
        vOrigin.push_back(i);
    }

    // 遍历打印
    for_each(vOrigin.begin(), vOrigin.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 目标容器
    vector<int> vTarget;
    // 手动分配内存空间
    vTarget.resize(vOrigin.size());
    // 将指定容器区间元素搬运到另一个容器中
    transform(vOrigin.begin(), vOrigin.end(), vTarget.begin(), MyTransForm());

    // 遍历打印
    for_each(vTarget.begin(), vTarget.end(), [](int value) { cout << value << " "; });

    cout << endl;
}

// 函数对象
class MyTransForm2 {

public:
    int operator()(int val1, int val2) {
        return val1 + val2;
    }

};

// 第二种使用方法
void test02() {

    cout << "----------- transform 的第二种用法 -------------" << endl;

    // 源容器
    vector<int> vOrigin1;
    vector<int> vOrigin2;

    int size = 10;
    for (int i = 0; i < size; i++) {
        vOrigin1.push_back(100 + i);
        vOrigin2.push_back(200 + i);
    }

    // 遍历打印
    for_each(vOrigin1.begin(), vOrigin1.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 遍历打印
    for_each(vOrigin2.begin(), vOrigin2.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // 目标容器
    vector<int> vTarget;
    // 手动分配内存空间
    vTarget.resize(size);
    // 将两个源容器的数据相加，然后搬运到目标容器
    transform(vOrigin1.begin(), vOrigin1.end(), vOrigin2.begin(), vTarget.begin(), MyTransForm2());

    // 遍历打印
    for_each(vTarget.begin(), vTarget.end(), [](int value) { cout << value << " "; });

}

int main() {
    test01();
    test02();
    return 0;
}
