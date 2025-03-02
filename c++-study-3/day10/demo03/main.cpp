/**
 * 实现带引用计数的智能指针
 */

#include <iostream>

using namespace std;

// 模拟实现带引用计数的智能指针（非线程安全）
template<typename T>
class RefCount {

public:
	RefCount(T* ptr = nullptr) : _ptr(ptr) {
        if (_ptr == nullptr) {
			_count = 0;
        }
        else {
            _count = 1;
        }
    }

    // 引用计算器自增
    void increDef() {
        _count++;
    }

    // 引用计算器自减
    int decreRef() {
		return _count > 0 ? --_count : 0;
    }

private:
    T* _ptr;        // 指向资源的指针
    int _count;     // 引用计时器
};

template<typename T>
class CSmartPtr {

public:
    // 构造函数
    CSmartPtr(T* ptr = nullptr) : _ptr(ptr) {
        cout << "CSmartPtr(T* ptr)" << endl;
        // 初始化引用计数对象
        _refCount = new RefCount<T>(_ptr);
    }

    // 析构函数
    ~CSmartPtr() {
        cout << "~CSmartPtr()" << endl;
        // 当引用计时器为零时，才释放智能指针管理的资源
		if (0 == _refCount->decreRef()) {
			delete _ptr;
			_ptr = nullptr;
        }
    }

    // 拷贝构造函数
    CSmartPtr(const CSmartPtr<T>& src) : _ptr(src._ptr), _refCount(src._refCount) {
        cout << "CSmartPtr(const CSmartPtr<T>& src)" << endl;
        // 引用计算器自增
        if (_ptr != nullptr) {
            _refCount->increDef();
        }
	}

    // 赋值运算符重载函数
    CSmartPtr<T> operator=(const CSmartPtr<T>& src) {
		cout << "CSmartPtr<T> operator=(const CSmartPtr<T>& src)" << endl;
        // 避免自赋值
        if (this == &src) {
			return *this;
        }

        // 释放资源
        if (0 == _refCount->decreRef()) {
            delete _ptr;
        }

        _ptr = src._ptr;
        _refCount = src._refCount;
        _refCount->increDef();

        return *this;
    }
    
    // * 运算符重载函数
    T& operator*() {
        return *_ptr;
    }

    // -> 运算符重载函数
    T* operator->() {
        return _ptr;
    }

private:
    T* _ptr;                   // 指向资源的指针
    RefCount<T>* _refCount;    // 指向资源引用计数对象的指针
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
    // 多个智能指针管理同一个资源
    CSmartPtr<Person> ptr1(new Person(20));
    CSmartPtr<Person> ptr2(ptr1);
    CSmartPtr<Person> ptr3;
    ptr3 = ptr2;
    
    ptr1->print();
    ptr2->print();
    ptr3->print();
}
