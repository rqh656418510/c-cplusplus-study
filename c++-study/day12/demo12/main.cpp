/*
 * 1. 绑定适配器的使用
 *
 * 第一步：绑定数据，如 bind2nd 或者 bind1st
 * 第二步：函数对象继承自 binary_function<参数类型１, 参数类型２, 返回值类型>
 * 第三步：operator() 加 const 修饰符
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 函数对象，继承自 binary_function
class MyPrint : public binary_function<int, int, void> {

public:

    void operator()(int v, int start) const {
        cout << v + start << " ";
    }

};

int main() {

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 0 ~ 9 加起始值，然后输出计算结果
    int num = 100;
    for_each(v.begin(), v.end(), bind2nd(MyPrint(), num));

    return 0;
}
