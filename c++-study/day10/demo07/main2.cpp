/*
 * 1. C++ �ļ� I/O ���ļ�ʹ��
 * a) �Զ����Ƶķ�ʽ��д�ļ�
*/

#include <iostream>
#include "fstream"

using namespace std;

class Teacher {

public:
	Teacher()
	{
		age = 33;
		strcpy(name, "");
	}

	Teacher(int _age, char* _name)
	{
		age = _age;
		strcpy(name, _name);
	}

	void print()
	{
		cout << "age:" << age << ", name:" << name << endl;
	}

private:
	int	age;
	char name[32];
};

int main() {
	char* fname = "D:/file.dat";
	ofstream fout(fname, ios::binary);
	if (!fout) {
		cout << "���ļ�ʧ��" << endl;
		return 0;
	}

	// �������д��������ļ������л���
	Teacher t1(23, "Jim");
	Teacher t2(26, "Tom");
	fout.write((char*)&t1, sizeof(Teacher));
	fout.write((char*)&t2, sizeof(Teacher));
	fout.flush();
	fout.close();

	ifstream fin(fname);
	if (!fin) {
		cout << "���ļ�ʧ��" << endl;
		return 0;
	}

	// �Ӷ������ļ���ȡ����󣨷����л���
	Teacher tmp;
	fin.read((char*)&tmp, sizeof(Teacher));
	tmp.print();
	fin.read((char*)&tmp, sizeof(Teacher));
	tmp.print();
	fin.close();

	return 0;
}