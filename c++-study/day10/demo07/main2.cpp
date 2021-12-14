/*
 * 1. C++ 文件 I/O 流的简单使用
 * a) 以二进制的方式读写文件
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
		cout << "打开文件失败" << endl;
		return 0;
	}

	// 将类对象写入二进制文件（序列化）
	Teacher t1(23, "Jim");
	Teacher t2(26, "Tom");
	fout.write((char*)&t1, sizeof(Teacher));
	fout.write((char*)&t2, sizeof(Teacher));
	fout.flush();
	fout.close();

	ifstream fin(fname);
	if (!fin) {
		cout << "打开文件失败" << endl;
		return 0;
	}

	// 从二进制文件读取类对象（反序列化）
	Teacher tmp;
	fin.read((char*)&tmp, sizeof(Teacher));
	tmp.print();
	fin.read((char*)&tmp, sizeof(Teacher));
	tmp.print();
	fin.close();

	return 0;
}