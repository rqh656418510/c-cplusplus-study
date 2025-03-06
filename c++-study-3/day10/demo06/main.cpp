/**
 * 自定义删除器
 */

#include <iostream>
#include <memory>

using namespace std;

// 自定义数组的删除器（函数对象）
template<typename T>
class ArrayDeleter {

public:
	void operator()(T * arrayPtr) const {
		cout << "Deleting array pointer" << endl;
		if (arrayPtr != nullptr) {
			delete[] arrayPtr;
		}
	}
};

// 自定义文件的删除器（函数对象）
template<typename T>
class FileDeleter {

public:
	void operator()(T* filePtr) const {
		cout << "Deleting file pointer" << endl;
		if (filePtr != nullptr) {
			fclose(filePtr);
		}
	}
};

int main() {
	// 创建一个智能指针管理整型数组，并指定删除器
	unique_ptr<int, ArrayDeleter<int>> ptr(new int[100]);

	// 创建一个智能指针管理文件，并指定删除器
	unique_ptr<FILE, FileDeleter<FILE>> ptr2(fopen("data.txt", "w"));

	return 0;
}