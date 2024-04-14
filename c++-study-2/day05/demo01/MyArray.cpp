#include "MyArray.h"

// 默认构造函数
MyArray::MyArray() {
    cout << "调用默认构造函数" << endl;
    this->m_Capacity = 100;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}

// 有参构造函数
MyArray::MyArray(int capacity) {
    cout << "调用有参构造函数" << endl;
    this->m_Capacity = capacity;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}

// 拷贝构造函数
MyArray::MyArray(const MyArray &array) {
    cout << "调用拷贝构造函数" << endl;
    this->m_Capacity = array.m_Capacity;
    this->m_Size = array.m_Size;
    // 分配数组内存空间
    this->pAddress = new int[this->m_Capacity];
    // 拷贝数组元素
    for (int i = 0; i < array.m_Size; i++) {
        this->pAddress[i] = array.pAddress[i];
    }
}

// 析构函数
MyArray::~MyArray() {
    cout << "调用析构函数" << endl;
    if (this->pAddress != nullptr) {
        delete[] this->pAddress;
        this->pAddress = nullptr;
    }
}

// 尾插数据
void MyArray::push_back(int value) {
    // 由用户自行处理数组的越界问题
    this->pAddress[m_Size] = value;
    this->m_Size++;
}

// 获取数据
int MyArray::get_data(int index) {
    // 由用户自行处理数组的越界问题
    return this->pAddress[index];
}

// 设置数据
void MyArray::set_data(int index, int value) {
    this->pAddress[index] = value;
}

// [] 运算符重载
int &MyArray::operator[](int index) {
    return this->pAddress[index];
}
