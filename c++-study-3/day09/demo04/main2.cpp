/**
 * move�ƶ������forward��������ת��
 * <p> move���ƶ����壬����ֵ����ǿתΪ��ֵ����
 * <p> forward����������ת�����ܹ�ʶ����ֵ���ͺ���ֵ����
 * 
 * <p>  move�ƶ����� + forward���͵�ʹ��
 */

#include <iostream>
#include <cstring>
#include "MyString.h"

using namespace std;

// ��ģ��
template<typename T>
// �ռ��������������ڴ濪�١��ڴ��ͷš������졢����������
struct Allocator {

    // ������ڴ濪��
    T* allocate(size_t size) {
        return (T*)malloc(sizeof(T) * size);
    }

    // ������ڴ��ͷ�
    void deallocate(void* p) {
        free(p);
    }

    // �����죨������ֵ���ò�����
    // ���ں���ģ����������� + �����۵�
    // T & + Ty &&  = T &
    // T && + Ty &&  = T &&
    template<typename Ty>
    void construct(T* p, Ty&& val) {
        // ��ָ�����ڴ��Ϲ�����󣨶�λ new��
        // forward �� C++ �е���������ת��
        new(p)T(forward<Ty>(val));
    }

    // ��������
    void destroy(T* p) {
        // ~T() ������ T ���Ͷ������������
        p->~T();
    }

};

// ��ģ��
template<typename T, typename Alloc = Allocator<T>>
// ��������
class Vector {

public:
    // ���캯��
    Vector(int size = 10) {
        // ����������ڴ�ռ�
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    // ���������������������ڵ���ЧԪ�أ�Ȼ�����ͷ� _first ָ��ָ��Ķ��ڴ棩
    ~Vector() {
        // ���������ڵ���ЧԪ��
        for (T* p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // �ͷŶ��ϵ������ڴ�
        _allocator.deallocate(_first);
        _first = _last = _end = nullptr;
    }

    // �������캯��
    Vector(const Vector<T>& v) {
        // �������ܴ�С
        int size = v._end - v._first;
        // ��ЧԪ�صĸ���
        int length = v._last - v._first;

        // ����������ڴ�ռ�
        _first = _allocator.allocate(size);

        // ��ָ�����ڴ�ռ��й������
        for (int i = 0; i < length; i++) {
            _allocator.construct(_first + i, v._first[i]);
        }
        _last = _first + length;
        _end = _first + size;
    }

    // ��ֵ���������
    Vector<T>& operator=(const Vector<T>& v) {
        if (this == v) {
            return *this;
        }

        // ���������ڵ���ЧԪ��
        for (T* p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // �ͷŶ��ϵ������ڴ�
        _allocator.deallocate(_first);

        // �������ܴ�С
        int size = v._end - v._first;
        // ��ЧԪ�صĸ���
        int length = v._last - v._first;

        // ����������ڴ�ռ�
        _first = _allocator.allocate(size);

        // ��ָ�����ڴ�ռ��й������
        for (int i = 0; i < length; i++) {
            _allocator.construct(_first + i, v._first[i]);
        }
        _last = _first + length;
        _end = _first + size;

        return *this;
    }

    // ������β�����Ԫ�أ�������ֵ���ò�����
    // ���ں���ģ����������� + �����۵�
    // T & + Ty &&  = T &
    // T && + Ty &&  = T &&
    template<typename Ty>
    void push_back(Ty &&val) {
        if (full()) {
            resize();
        }
        // ��ָ�����ڴ�ռ��й������
        // forward �� C++ �е���������ת��
        _allocator.construct(_last, forward<Ty>(val));
        _last++;
    }

    // ������β��ɾ��Ԫ�أ���Ҫ��������������ڴ��ͷŷֿ�����
    void pop_back() {
        if (!empty()) {
            _last--;
            // ��ָ�����ڴ�ռ�����������
            _allocator.destroy(_last);
        }
    }

    // ��������β����Ԫ��
    T back() const {
        if (empty()) {
            throw "Vector is empty!";
        }
        return *(_last - 1);
    }

    // �����Ƿ�����
    bool full() const {
        return _last == _end;
    }

    // �����Ƿ�Ϊ��
    bool empty() const {
        return _first == _last;
    }

    // ������ЧԪ�صĸ���
    int size() const {
        return _last - _first;
    }

    // ���������������
    T& operator[](int index) {
        if (index < 0 || index >= size()) {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    // ������
    class iterator {

    public:
        iterator(T* p = nullptr) : _ptr(p) {

        }

        // ���ز����������
        bool operator!=(const iterator& other) const {
            return _ptr != other._ptr;
        }

        // ����ǰ�� ++ �����
        iterator& operator++() {
            _ptr++;
            return *this;
        }

        // ���غ��� ++ �����
        iterator operator++(int) {
            return iterator(_ptr++);
        }

        // ���������������
        T& operator*() const {
            return *_ptr;
        }

    private:
        T* _ptr;
    };

    // ���ص��������ײ���Ԫ�صĵ������ı�ʾ
    iterator begin() {
        return iterator(_first);
    }

    // ���ص�������ĩβԪ�غ��λ�õĵ������ı�ʾ
    iterator end() {
        return iterator(_last);
    }

private:
    T* _first;  // ָ��������ʼ��λ��
    T* _last;   // ָ����������ЧԪ�صĺ��λ��
    T* _end;    // ָ������ռ�ĺ��λ��
    Alloc _allocator;   // ���������ռ��������Ķ���

    // ���ݲ���
    void resize() {
        int size = _end - _first;
        // ����������ڴ�ռ�
        T* _ptemp = _allocator.allocate(size * 2);
        // ��ָ�����ڴ�ռ��й������
        for (int i = 0; i < size; i++) {
            _allocator.construct(_ptemp + i, _first[i]);
        }

        // ����ԭ�������ڵ���ЧԪ��
        for (T* p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // �ͷ�ԭ���������ڴ�
        _allocator.deallocate(_first);

        _first = _ptemp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};

class Person {

public:
    Person() {
        cout << "call Person()" << endl;
    }

    Person(const Person& p) {
        cout << "call Person(const Person &p)" << endl;
    }

    ~Person() {
        cout << "call ~Person()" << endl;
    }

};

void test01() {
    cout << "\n============ test01() ============" << endl;

    MyString str1 = "aaa";
    Vector<MyString> v1;

    cout << "----------------------------------" << endl;
    v1.push_back(str1); // ���õ��Ǵ���ֵ���ò����Ŀ������캯��
    cout << "----------------------------------" << endl;
}

void test02() {
    cout << "\n============ test02() ============" << endl;

    Vector<MyString> v1;
    cout << "----------------------------------" << endl;
    v1.push_back(MyString("bbb"));  // ���õ��Ǵ���ֵ���ò����Ŀ������캯�� 
    cout << "----------------------------------" << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
