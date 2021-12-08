/*
 * 1. C++ �ļ� I/O ���ļ�ʹ��
 * a) ����ͨ�ķ�ʽ��д�ļ�
*/

#include <iostream>
#include "fstream"

using namespace std;

void writeFile() {
	// ���ļ�
	char* fname = "D:/file.txt";
	ofstream fout(fname);
	if (fout) {
		fout << "Hello World" << endl;
		fout.flush();
		fout.close();
	}
}

void readFile() {
	// ��ȡ�ļ�
	char ch;
	char* fname = "D:/file.txt";
	ifstream fin(fname);
	if (fin) {
		while (fin.get(ch)) {
			cout << ch;
		}
		fin.close();
	}
}

void writeFileApp() {
	// ��׷�ӵķ�ʽ���ļ�
	char* fname = "D:/file.txt";
	ofstream fout(fname, ios::app);
	if (fout) {
		fout << "What" << endl;
		fout.flush();
		fout.close();
	}
}

int main() {
	writeFile();
	readFile();
	writeFileApp();
	readFile();
	return 0;
}