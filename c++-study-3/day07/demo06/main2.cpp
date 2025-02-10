/**
 * 函数对象
 *
 * <p> 函数对象的使用
 */

#include <iostream>

using namespace std;

template<typename T>
// 函数对象
class mygreater {

public:
    bool operator()(T a, T b) {
        return a > b;
    }

};

template<typename T>
// 函数对象
class myless {

public:
    bool operator()(T a, T b) {
        return a < b;
    }

};

// Compare 是 C++ 的库函数模板
template<typename T, typename Compare>
bool compare(T a, T b, Compare func) {
    // 这里调用函数对象，会产生内联，执行效率比较高，没有函数调用的开销
    return func(a, b);
}

int main() {
    cout << compare(1, 3, mygreater<int>()) << endl;
    cout << compare(1, 3, myless<int>()) << endl;
    return 0;
}
