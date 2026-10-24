/**
 * 萃取(traits)技术概念、范例等
 *
 * (a) 类型萃取
 */

#include <iostream>
#include <list>
#include <type_traits>
#include <typeinfo>

using namespace std;

template<typename T>
void printTraitsInfo(const T &t) {
    cout << "------------begin------------" << endl;
    cout << "type name: " << typeid(T).name() << endl;
    cout << "is_void = " << is_void<T>::value << endl;                                                        // 类型是否是 void
    cout << "is_class = " << is_class<T>::value << endl;                                                      // 类型是否是一个 class
    cout << "is_object = " << is_object<T>::value << endl;                                                    // 类型是否是一个对象类型
    cout << "is_pod = " << is_pod<T>::value << endl;                                                          // 是否是 POD 类型（只拥有成员变量，不拥有成员函数）
    cout << "is_default_constructible = " << is_default_constructible<T>::value << endl;                      // 是否有默认构造函数
    cout << "is_copy_constructible = " << is_copy_constructible<T>::value << endl;                            // 是否有拷贝构造函数
    cout << "is_move_constructible = " << is_move_constructible<T>::value << endl;                            // 是否有移动构造函数
    cout << "is_destructible = " << is_destructible<T>::value << endl;                                        // 是否有析构函数
    cout << "is_polymorphic = " << is_polymorphic<T>::value << endl;                                          // 是否含有虚函数
    // cout << "has_trivial_default_constructor = " << has_trivial_default_constructor<T>::value << endl;     // 是否有平凡默认构造
    cout << "has_virtual_destructor = " << has_virtual_destructor<T>::value << endl;                          // 是否有虚析构函数
    cout << "------------end------------" << endl;
}

class A {
public:
    A() = default;            // 默认构造函数
    A(A &&ta) = delete;       // 移动构造：如果不写delete，系统一般就会认为有这个成员函数
    A(const A &ta) = delete;  // 拷贝构造
    virtual ~A() {            // 虚析构
    }
};

class B {
public:
    int m_i;
    int m_j;
};

class C {
public:
    C(int val) {  // 有参构造函数，编译器不会再提供默认构造函数
    }
};

int main() {
    printTraitsInfo(int());
    printTraitsInfo(string());
    printTraitsInfo(A());
    printTraitsInfo(B());
    printTraitsInfo(C(10));
    printTraitsInfo(list<int>());
}
