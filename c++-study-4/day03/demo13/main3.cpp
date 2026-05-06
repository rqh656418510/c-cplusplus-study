/*
 * 可变参模板
 *
 * (c) 可变参类模板
 */

#include <iostream>

using namespace std;

// 定义可变参类模板（主模板）
template <typename... Others>
class myclasst;

// 特例化终止
template <>
class myclasst<> {
public:
    // 默认构造函数
    myclasst() {
        cout << "特例化终止, address = " << this << endl;
    }
};

// 使用递归继承展开参数包
template <typename First, typename... Others>
class myclasst<First, Others...> : private myclasst<Others...> {  // 类偏特化
public:
    // 默认构造函数
    myclasst() {
        cout << "address = " << this << endl;
    }

    // 有参构造函数
    myclasst(First first, Others... others) : m_first(first), myclasst<Others...>(others...) {
        cout << "address = " << this << endl;
        // 获取模板参数的数量
        cout << "size = " << sizeof...(others) << endl;
        // 获取模板参数的值
        cout << "value = " << m_first << endl;
    }

public:
    First m_first;
};

int main() {
    myclasst<int, float, double> myc(2, 1.2f, 3.45);
    return 0;
}