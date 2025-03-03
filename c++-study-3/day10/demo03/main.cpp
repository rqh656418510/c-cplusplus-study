/**
 * 实现带引用计数的智能指针
 */

#include <iostream>

using namespace std;

// 模拟实现带引用计数的智能指针（不考虑线程安全问题），类似 shared_ptr 智能指针
template<typename T>
class RefCount {

public:
    RefCount(T *ptr = nullptr) : _ptr(ptr) {
        // 在堆上初始化引用计数，为了让智能指针在复制或赋值时共享同一个引用计数
        if (_ptr == nullptr) {
            _count = new int(0);
        } else {
            _count = new int(1);
        }
    }

    ~RefCount() {
        // 释放堆上的引用计数
        delete _count;
    }

    // 引用计数自增
    void increDef() {
        ++(*_count);
    }

    // 引用计数自减
    int decreRef() {
        if (*_count > 0) {
            return --(*_count);
        }
        return 0;
    }

    // 获取当前引用计数
    int getCount() const {
        return *_count;
    }

private:
    T *_ptr;        // 指向资源的指针
    int *_count;    // 指向堆上存储的引用计数
};

template<typename T>
class CSmartPtr {

public:
    // 构造函数
    CSmartPtr(T *ptr = nullptr) : _ptr(ptr) {
        cout << "CSmartPtr(T* ptr)" << endl;
        // 初始化引用计数对象
        _refCount = new RefCount<T>(_ptr);
    }

    // 析构函数
    ~CSmartPtr() {
        cout << "~CSmartPtr()" << endl;
        // 减少引用计数，并且当引用计数为零时，才释放智能指针管理的资源
        if (0 == _refCount->decreRef()) {
            delete _ptr;
            delete _refCount;
        }
    }

    // 拷贝构造函数
    CSmartPtr(const CSmartPtr<T> &src) : _ptr(src._ptr), _refCount(src._refCount) {
        cout << "CSmartPtr(const CSmartPtr<T>& src)" << endl;
        // 增加引用计数
        if (_ptr != nullptr) {
            _refCount->increDef();
        }
    }

    // 赋值运算符重载函数
    CSmartPtr<T> &operator=(const CSmartPtr<T> &src) {
        cout << "CSmartPtr<T> operator=(const CSmartPtr<T>& src)" << endl;
        // 避免自赋值
        if (this == &src) {
            return *this;
        }

        // 释放旧的资源
        if (0 == _refCount->decreRef()) {
            delete _ptr;
            delete _refCount;
        }

        // 共享新的资源
        _ptr = src._ptr;
        _refCount = src._refCount;

        // 增加引用计数
        _refCount->increDef();

        return *this;
    }

    // * 运算符重载函数
    T &operator*() {
        return *_ptr;
    }

    // -> 运算符重载函数
    T *operator->() {
        return _ptr;
    }

private:
    T *_ptr;                   // 指向资源的指针
    RefCount<T> *_refCount;    // 指向资源引用计数对象的指针
};

class Person {

public:
    Person(int age = 0) : _age(age) {
        cout << "Person(int age)" << endl;
    }

    ~Person() {
        cout << "~Person()" << endl;
    }

    void print() {
        cout << "age: " << _age << endl;
    }

private:
    int _age;
};

int main() {
    // 测试多个智能指针管理同一个对象资源
    CSmartPtr<Person> ptr1(new Person(20));

    {
        CSmartPtr<Person> ptr2(ptr1);   // 可复制
        ptr2->print();

        CSmartPtr<Person> ptr3;
        ptr3 = ptr2;                    // 可赋值
        ptr3->print();
    } // 出了作用域后，ptr2、ptr3 析构，但不影响 ptr1，也不影响对象资源的析构

    cout << "Leaving inner scope..." << endl;

    ptr1->print();  // 仍然有效

} // 出了作用域后，ptr1 析构，并析构对象资源
