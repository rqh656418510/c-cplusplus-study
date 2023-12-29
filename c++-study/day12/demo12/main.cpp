/*
 * 1. #### 常用函数适配器的使用
 *
 * 第一步：绑定数据，如 bind2nd 或者 bind1st
 * 第二步：函数对象继承类 binary_function<参数类型１, 参数类型２, 返回值类型>
 * 第三步：operator() 加 const 修饰符
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 函数对象
class MyPrint : public binary_function<int, int, void> {

public:

    void operator()(int v, int start) const {
        cout << v + start << " ";
    }

};

void test01() {
    cout << "------ 绑定适配器（binder）的使用 ------" << endl;

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 0 ~ 9 加起始值，然后输出计算结果
    int num = 100;
    for_each(v.begin(), v.end(), bind2nd(MyPrint(), num));

    cout << endl;
}

// 函数对象
class GreaterThenFive : public unary_function<int, bool> {

public:

    bool operator()(int v) const {
        return v > 5;
    }

};

void test02() {
    cout << "------ 取反适配器（negator）的使用 ------" << endl;

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 查找第一个小于５的数字
    vector<int>::iterator pos = find_if(v.begin(), v.end(), not1(GreaterThenFive()));
    if (pos != v.end()) {
        cout << "found first number less then five is " << *pos << endl;
    } else {
        cout << "not found first number less then five" << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}
