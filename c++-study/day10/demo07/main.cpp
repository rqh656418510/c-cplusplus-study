/*
 * 1. C++ 文件 I/O 流的简单使用
 * a) 以普通的方式读写文件
*/

#include <iostream>
#include "fstream"

using namespace std;

void writeFile() {
	// 打开文件
	char* fname = "D:/file.txt";
	ofstream fout(fname);
	if (fout) {
		fout << "Hello World" << endl;
		fout.flush();
		fout.close();
	}
}

void readFile() {
	// 读取文件
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
	// 以追加的方式打开文件
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