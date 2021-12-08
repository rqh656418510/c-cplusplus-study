#include "Teacher.h"

// ���캯��
Teacher::Teacher() {
	this->m_age = 0;
	this->m_name = (char*)malloc(1);
	if (this->m_name) {
		strcpy(this->m_name, "");
	}
}

// ���캯��
Teacher::Teacher(int age, const char* name) {
	this->m_age = age;
	this->m_name = (char*)malloc(strlen(name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, name);
	}
}

// �������캯��
Teacher::Teacher(const Teacher& obj) {
	// ���
	this->m_age = obj.m_age;
	this->m_name = (char*)malloc(strlen(obj.m_name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, obj.m_name);
	}
}

// ��������
Teacher::~Teacher() {
	if (this->m_name) {
		free(this->m_name);
	}
}

// ʹ�����Ա��������������� "="
Teacher& Teacher::operator=(const Teacher& obj) {
	// �ͷ�ԭ�����ڴ�ռ�
	if (this->m_name) {
		free(this->m_name);
		this->m_name = NULL;
	}
	// ���
	this->m_age = obj.m_age;
	this->m_name = (char*)malloc(strlen(obj.m_name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, obj.m_name);
	}
	return *this;
}

// ʹ����Ԫ��������������� "<<"
ostream& operator<<(ostream& out, Teacher& obj) {
	cout << "age = " << obj.m_age << " name = " << obj.m_name;
	return out;
}

int Teacher::getAge() {
	return this->m_age;
}

char* Teacher::getName() {
	return this->m_name;
}

void Teacher::setAge(int age) {
	this->m_age = age;
}

void Teacher::setName(const char* name) {
	// �ͷ�ԭ�����ڴ�ռ�
	if (this->m_name) {
		free(this->m_name);
		this->m_name = NULL;
	}
	// ���
	this->m_name = (char*)malloc(strlen(name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, name);
	}
}