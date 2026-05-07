/*
 * 可变参模板续、模板模板参数
 *
 * (b) 可变参类模板：通过 std::tuple 和递归调用展开参数包
 */

#include <iostream>
#include <tuple>

using namespace std;

// 定义可变参类模板
template <int curCount, int argsTotal, typename... T>
class myclasst {
public:
    static void print(const tuple<T...>& t) {
        cout << get<curCount>(t) << endl;
        // 递归调用
        myclasst<curCount + 1, argsTotal, T...>::print(t);
    }
};

// 特化终止，用于结束递归调用
template <int curCount, typename... T>
class myclasst<curCount, curCount, T...> {
public:
    static void print(const tuple<T...>& t) {
        cout << "特化终止" << endl;
    }
};

// 定义可变参函数模板
template <typename... T>
void print(const tuple<T...>& t) {
    myclasst<0, sizeof...(T), T...>::print(t);
}

int main() {
    tuple<int, float, double> t(2, 2.5f, 3.14);
    print(t);
    return 0;
}
