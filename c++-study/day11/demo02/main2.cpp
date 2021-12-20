/*
 * 1. string容器的API
*/

#include <iostream>

using namespace std;

int main() {
    // 存储字符
    string str1 = "abcde";
    for (int i = 0; i < str1.size(); i++) {
        // 第一种方式
        cout << str1[i] << " ";
        // 第二种方式
        // cout << str1.at(i) << " ";
    }
    cout << endl;

    // 字符串拼接
    string str2 = "hello ";
    string str3 = "world ";
    str2 += str3;
    str3.append("where");
    cout << "str2 = " << str2 << endl;
    cout << "str3 = " << str3 << endl;

    // 字符串查找
    string str4 = "My name is Peter";
    int index1 = str4.find("name");
    cout << "index1 = " << index1 << endl;
    int index2 = str4.rfind("e");
    cout << "index2 = " << index2 << endl;

    // 字符串替换
    string str5 = "abc123";
    str5.replace(3, 3, "def");
    cout << "str5 = " << str5 << endl;
    string str6 = "123456";
    string str7 = "654321";
    str6.swap(str7);
    cout << "str6 = " << str6 << endl;

    // 字符串比较
    string str8 = "ABC";
    string str9 = "abc";
    int result = str8.compare(str9);    // 返回值小于等于-1
    cout << "result = " << result << endl;

    // 截取子字符串
    string str10 = "124abc";
    string str11 = str10.substr(1, 3);
    cout << "str11 = " << str11 << endl;

    // 字符串的区间插入
    string str12 = "abcdef";
    str12.insert(2, "123");
    cout << "str12 = " << str12 << endl;

    // 字符串的区间删除
    string str13 = "123456";
    str13.erase(2, 2);
    cout << "str13 = " << str13 << endl;

    // 从字符串取得 char *
    string str14 = "hijkl";
    const char *p1 = str14.c_str();
    cout << "p1 = " << p1 << endl;

    // char * 隐式类型转换为 string
    char *p2 = "abc123";
    string str15 = p2;
    cout << "str15 = " << str15 << endl;

    // 将 string 拷贝到 char* 指向的内存空间
    char *p3 = new char[3];
    string str16 = "hello jim";
    int number = str16.copy(p3, 3, 2);
    cout << "number = " << number << endl;
    cout << "p3 = " << p3 << endl;
    delete[] p3;

    return 0;
}