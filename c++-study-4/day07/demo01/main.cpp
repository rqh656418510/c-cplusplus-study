/**
 * STL总述、发展史、组成，数据结构谈
 *
 * (a) array（数组）使用
 */

#include <array>
#include <iostream>
#include <string>

using namespace std;

int main() {
    array<string, 3> arr = {"I", "Love", "C++"};

    cout << "array size: " << arr.size() << endl;

    cout << "string size: " << sizeof(string) << endl;

    for (int i = 0; i < arr.size(); i++) {
        cout << "--------------------------" << endl;
        const char* ptr = arr[i].c_str();
        cout << "Array element value: " << arr[i] << endl;
        cout << "Address of the array element: " << &arr[i] << endl;                      // 表示 std::string 对象本身的地址
        printf("Address of the string it points to: 0x%llx\n", (unsigned long long)ptr);  // 表示字符串字符数据存储的起始地址
    }

    return 0;
}