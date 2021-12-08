#include "MyString.h"

// �޲ι��캯��
MyString::MyString() {
	// ��ʼ��Ϊ���ַ���
	this->m_length = 0;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, "");
}

// �вι��캯��
MyString::MyString(int len) {
	if (len < 0) {
		len = 0;
	}
	// ��ʼ��Ϊ���ַ���
	this->m_length = len;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, "");
}

// �вι��캯��
MyString::MyString(const char* p) {
	if (p == NULL) {
		// ��ʼ��Ϊ���ַ���
		this->m_length = 0;
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, "");
	}
	else {
		this->m_length = strlen(p);
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, p);
	}
}

// �������캯��
MyString::MyString(const MyString& str) {
	// ��������·����ڴ�ռ�
	this->m_length = str.m_length;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, str.m_space);
}

// ��������
MyString::~MyString() {
	// �ͷ��ڴ�ռ�
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
}

// ʹ�����Ա�������� "[]" �����
char& MyString::operator[](int index) {
	return this->m_space[index];
}

// ʹ�����Ա�������� "=" �����
MyString& MyString::operator=(const char* p) {
	// �ͷ��ڴ�ռ�
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// ��������·����ڴ�ռ�
	if (p == NULL) {
		// ��ʼ��Ϊ���ַ���
		this->m_length = 0;
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, "");
	}
	else {
		this->m_length = strlen(p);
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, p);
	}
	return *this;
}

// ʹ�����Ա�������� "=" �����
MyString& MyString::operator=(const MyString& str) {
	// �ͷ��ڴ�ռ�
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// ��������·����ڴ�ռ�
	this->m_length = str.m_length;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, str.m_space);
	return *this;
}

// ʹ�����Ա�������� "==" �����
bool MyString::operator==(const char* p) const {
	if (p == NULL) {
		if (this->m_length == 0) {
			return true;
		}
		return false;
	}
	if (this->m_length != strlen(p)) {
		return false;
	}
	return !strcmp(this->m_space, p);
}

bool MyString::operator==(const MyString str) const {
	if (this->m_length != str.m_length) {
		return false;
	}
	return !strcmp(this->m_space, str.m_space);
}

// ʹ�����Ա�������� "!=" �����
bool MyString::operator!=(const char* p) const {
	return !(*this == p);
}

bool MyString::operator!=(const MyString str) const {
	return !(*this == str);
}

// ʹ�����Ա�������� ">" �����
bool MyString::operator>(const char* p) const {
	return strcmp(p, this->m_space) < 0;
}

bool MyString::operator>(const MyString str) const {
	return strcmp(str.m_space, this->m_space) < 0;
}

// ʹ�����Ա�������� "<" �����
bool MyString::operator<(const char* p) const {
	return strcmp(this->m_space, p) < 0;
}

bool MyString::operator<(const MyString str) const {
	return strcmp(this->m_space, str.m_space) < 0;
}

// ʹ����Ԫ�������� "<<" �����
ostream& operator<<(ostream& out, MyString& str) {
	out << str.m_space;
	return out;
}

// ʹ����Ԫ�������� ">>" �����
iostream& operator>>(iostream& in, MyString& str)
{
	in >> str.m_space;
	return in;
}

int MyString::length()
{
	return this->m_length;
}

char* MyString::c_str() {
	return this->m_space;
}