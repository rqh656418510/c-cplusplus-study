/**
 * �Զ��� String ��
 */

#pragma

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class MyString {

public:
    // ���캯��
    MyString(const char* p = nullptr) {
        cout << "MyString(const char *p = nullptr)" << endl;
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        }
        else {
            _pstr = new char[1];
            *_pstr = '\0';
        }
    }

    // ��������
    ~MyString() {
        cout << "~MyString()" << endl;
        delete[] _pstr;
        _pstr = nullptr;
    }

    // ����ֵ���ò����Ŀ������캯��
    MyString(const MyString& str) {
        cout << "MyString(const MyString &str)" << endl;
        // ���
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }

    // ����ֵ���ò����Ŀ������캯��
    MyString(MyString&& str) {
        cout << "MyString(MyString&& str)" << endl;
        // ǳ������ʱ���󣨿�����ߴ���ִ��Ч�ʣ������ڴ�Ŀ���������
        _pstr = str._pstr;
        str._pstr = nullptr;
    }

    // ����ֵ���ò����ĸ�ֵ���������
    MyString& operator=(const MyString& str) {
        cout << "operator=(const MyString &str)" << endl;
        // ��ֹ�Ը�ֵ
        if (this == &str) {
            return *this;
        }

        // �ͷ�ԭ�����ڴ�ռ�
        delete[] _pstr;

        // ���
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);

        return *this;
    }

    // ����ֵ���ò����ĸ�ֵ���������
    MyString& operator=(MyString&& str) {
        cout << "operator=(MyString&& str)" << endl;
        // ��ֹ�Ը�ֵ
        if (this == &str) {
            return *this;
        }

        // �ͷ�ԭ�����ڴ�ռ�
        delete[] _pstr;

        // ǳ������ʱ���󣨿�����ߴ���ִ��Ч�ʣ������ڴ�Ŀ���������
        _pstr = str._pstr;
        str._pstr = nullptr;

        return *this;
    }


    // �ӷ����������
    friend MyString operator+(const MyString& str1, const MyString& str2);

    // �������������
    friend ostream& operator<<(ostream& out, const MyString& str);

    // �����ַ�������
    const char* c_str() const {
        return _pstr;
    }

private:
    char* _pstr;
};

MyString operator+(const MyString& str1, const MyString& str2) {
    MyString tmpStr;
    tmpStr._pstr = new char[strlen(str1._pstr) + strlen(str2._pstr) + 1];
    strcpy(tmpStr._pstr, str1._pstr);
    strcat(tmpStr._pstr, str2._pstr);
    return tmpStr;
}

ostream& operator<<(ostream& out, const MyString& str) {
    out << str._pstr;
    return out;
}