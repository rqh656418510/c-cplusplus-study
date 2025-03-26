/**
 * bind1st和bind2nd什么时候会用到
 *
 * <p> 在 C++ 11 及更新版本中，`bind1st` 和 `bind2nd` 已被 `bind` 取代
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> vec = {5, 2, 4, 1, 6};

    // 查找第一个小于 3 的元素

    // 使用 bind 绑定 greater 的第一个参数，等价于 f(x) = (3 > x)
    function<bool(int)> predicate = bind(greater<int>(), 3, placeholders::_1);

    // 使用 bind 绑定 greater 的第二个参数，等价于 f(x) = (x < 3)
    // function<bool(int)> predicate = bind(less<int>(), placeholders::_1, 3);

    vector<int>::iterator it = find_if(vec.begin(), vec.end(), predicate);

    if (it != vec.end()) {
        cout << "找到小于 3 的第一个元素：" << *it << endl;
    } else {
        cout << "未找到符合条件的元素" << endl;
    }

    return 0;
}
