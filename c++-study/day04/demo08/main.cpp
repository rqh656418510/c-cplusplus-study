/**
 * 1. ���صȺ������
 */

#include <iostream>
#include "string.h"

using namespace std;

class Name {

private:
	char* p;
	int len;

public:

	Name(const char* name) {
		cout << "�вι��캯����������" << endl;
		len = strlen(name);
		p = new char[len + 1];
		strcpy(p, name);
	}

	// �����ʵ��
	Name(const Name& name) {
		cout << "�������캯����������" << endl;
		len = name.getLen();
		p = new char[len + 1];
		strcpy(p, name.getP());
	}

	~Name() {
		cout << "����������������" << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
			len = 0;
		}
	}

	char* getP() const {
		return p;
	}

	int getLen() const {
		return len;
	}

public:
	// ʹ�����Ա����ʵ�� "=" ������������
	Name& operator=(const Name& n) {
		// �ͷ��ڴ�ռ�
		if (p != NULL) {
			delete[] p;
			p = NULL;
			len = 0;
		}
		// ���·����ڴ�ռ�
		len = n.getLen();
		p = new char[len + 1];
		strcpy(p, n.getP());
		return *this;
	}
};

int main() {
	Name obj1("Peter");
	Name obj2("Tom");
	Name obj4("Tim");

	// ���Զ����ÿ������캯�������������
	Name obj3 = obj1;
	cout << "obj3.name: " << obj3.getP() << ", obj3.len:  " << obj3.getLen() << endl;
	
	// �����Զ����ÿ������캯��������ǳ������
	// Ĭ������£������ﲻ�� "=" ������������أ����ճ�����쳣��ֹ���У�ͬһ���ڴ�ռ䱻�ͷ����ε��£�
	obj4 = obj1;
	cout << "obj4.name: " << obj4.getP() << ", obj4.len:  " << obj4.getLen() << endl;
	
	return 0;
}