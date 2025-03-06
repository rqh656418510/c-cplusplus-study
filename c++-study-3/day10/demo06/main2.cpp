/**
 * 自定义删除器
 */

#include <iostream>
#include <memory>
#include <functional>

using namespace std;

int main() {
	// 创建一个智能指针管理整型数组，并通过Lambda表达指定删除器
	unique_ptr<int, function<void(int*)>> ptr(new int[100], [](int* p) {
		cout << "Deleting array pointer by lambda" << endl;
		delete[] p;
	});


	// 创建一个智能指针管理文件，并通过Lambda表达指定删除器
	unique_ptr<FILE, function<void(FILE*)>> ptr2(fopen("data.txt", "w"), [](FILE* p) {
		cout << "Deleting file pointer by lambda" << endl;
		fclose(p);
	});

	return 0;
}