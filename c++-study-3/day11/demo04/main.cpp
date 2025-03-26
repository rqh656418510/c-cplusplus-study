/**
 * bind1st和bind2nd什么时候会用到
 *
 * <p> bind1st：绑定二元（两个参数）函数对象的第一个参数，生成一个新的函数对象，该函数对象接收原函数的第二个参数作为输入。
 * <p> bind2nd：绑定二元（两个参数）函数对象的第二个参数，生成一个新的函数对象，该函数对象接收原函数的第一个参数作为输入。
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

// 函数模板
template<typename Container>
void showContainer(Container &con) {
    // 遍历容器并打印元素
    typename Container::iterator it = con.begin();
    for (; it != con.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void test01() {
    vector<int> vec;

    for (int i = 0; i < 10; i++) {
        vec.push_back(rand() % 100 + 1);
    }

    showContainer(vec);

    // 从小到大排序
    sort(vec.begin(), vec.end());

    showContainer(vec);

    // 从大到小排序，greater 是二元函数对象
    sort(vec.begin(), vec.end(), greater<int>());

    showContainer(vec);
}

void test02() {
    vector<int> vec;

    for (int i = 0; i < 10; i++) {
        vec.push_back(rand() % 100 + 1);
    }

    showContainer(vec);

    // 从小到大排序
    sort(vec.begin(), vec.end(), greater<int>());

    showContainer(vec);

    // 查找第一个小于 70 的元素

    // 使用 bind1st 绑定 greater 的第一个参数，使其始终为 70，让 greater(70, x) 变成一元函数对象，等价于 f(x) = (70 > x)
    vector<int>::iterator it = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));

    // 使用 bind2nd 绑定 less 的第二个参数，使其始终为 70，让 less(x, 70) 变成一元函数对象，等价于 f(x) = (x < 70)
    // vector<int>::iterator it = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));

    if (it != vec.end()) {
        cout << "找到小于 70 的第一个元素：" << *it << endl;
    } else {
        cout << "未找到符合条件的元素" << endl;
    }
}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    test01();

    cout << "================================" << endl;

    test02();

    return 0;
}
