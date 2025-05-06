/**
 * C++11容器emplace方法原理剖析二
 *
 * <p> 模拟实现 vector 容器的 emplace_back() 函数
 */

#include <iostream>
#include <stdexcept>

using namespace std;

// 容器的空间配置器
template<typename T>
struct MyAllocator {

    // 申请内存
    T *allocate(size_t size) {
        return (T *) malloc(size * sizeof(T));
    }

    // 释放内存
    void deallocate(T *p) {
        free(p);
    }

    // 对象构造
    template<typename... Types>
    void construct(T *ptr, Types &&... args) {
        // 在指定的内存上构造对象（定位 new）
        new(ptr)T(forward<Types>(args)...);
    }

    // 对象析构
    void destroy(T *p) {
        // ~T() 代表了 T 类型对象的析构函数
        p->~T();
    }

};

// 自定义 Vector 容器
template<typename T, typename Alloc = MyAllocator<T>>
class MyVector {

public:
    // 构造函数
    MyVector(int size = 10) {
        _idx = 0;
        _size = size;

        // 分配内存空间
        _vec = _allocator.allocate(size);

        // 检查内存分配结果
        if (!_vec) {
            throw bad_alloc();
        }
    }

    // 析构函数
    ~MyVector() {
        // 析构容器内的有效元素
        for (int i = 0; i < _idx; i++) {
            _allocator.destroy(_vec + i);
        }

        // 释放堆上的内存
        _allocator.deallocate(_vec);
    }

    // 禁止拷贝
    MyVector(const MyVector &v) = delete;

    // 禁止赋值
    MyVector &operator=(const MyVector v) = delete;

    // 往尾部插入元素，基于引用折叠 + 类型完美转发
    template<typename Type>
    void push_back(Type &&val) {
        if (_idx >= _size) {
            throw out_of_range("Vector capacity exceeded.");
        }

        _allocator.construct(_vec + _idx, forward<Type>(val));
        _idx++;
    }

    // 往尾部插入元素，基于可变参数模板 + 引用折叠 + 类型完美转发
    template<typename... Types>
    void emplace_back(Types &&... args) {
        if (_idx >= _size) {
            throw out_of_range("Vector capacity exceeded.");
        }

        _allocator.construct(_vec + _idx, forward<Types>(args)...);
        _idx++;
    }

private:
    T *_vec;            // 指向容器的内存首地址
    size_t _size;       // 容器的大小
    size_t _idx;        // 容器最新元素的位置
    Alloc _allocator;   // 空间配置器

};

////////////////////////////////////////////////////////////////////////////////////////

class Test {

public:

    Test(int a) {
        cout << "Test(int)" << endl;
    }

    Test(int a, int b) {
        cout << "Test(int, int)" << endl;
    }

    // 析构函数
    ~Test() {
        cout << "~Test()" << endl;
    }

    // 带左值引用的拷贝构造函数
    Test(const Test &) {
        cout << "Test(const Test &)" << endl;
    }

    // 带右值引用的拷贝构造函数
    Test(Test &&) {
        cout << "Test(Test &&)" << endl;
    }

};

void test01() {
    cout << "============ test01 ===========" << endl;

    Test t1(10);
    MyVector<Test> v1;

    // 如果直接插入普通对象，两者没有任何区别
    v1.push_back(t1);
    v1.emplace_back(t1);
}

void test02() {
    cout << "============ test02 ===========" << endl;

    MyVector<Test> v1;

    // 如果直接插入临时对象，两者没有任何区别
    v1.push_back(Test(20));
    v1.emplace_back(Test(20));
}

void test03() {
    cout << "============ test03 ===========" << endl;

    MyVector<Test> v1;

    // 给emplace_back()传入Test对象构造所需要的参数，会直接在容器底层调用对象的构造函数，即不会产生临时对象
    v1.emplace_back(30);
    v1.emplace_back(40, 50);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
