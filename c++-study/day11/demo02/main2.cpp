/*
 * 1. string������API
*/

#include <iostream>

using namespace std;

int main() {
    // �洢�ַ�
    string str1 = "abcde";
    for (int i = 0; i < str1.size(); i++) {
        // ��һ�ַ�ʽ
        cout << str1[i] << " ";
        // �ڶ��ַ�ʽ
        // cout << str1.at(i) << " ";
    }
    cout << endl;

    // �ַ���ƴ��
    string str2 = "hello ";
    string str3 = "world ";
    str2 += str3;
    str3.append("where");
    cout << "str2 = " << str2 << endl;
    cout << "str3 = " << str3 << endl;

    // �ַ�������
    string str4 = "My name is Peter";
    int index1 = str4.find("name");
    cout << "index1 = " << index1 << endl;
    int index2 = str4.rfind("e");
    cout << "index2 = " << index2 << endl;

    // �ַ����滻
    string str5 = "abc123";
    str5.replace(3, 3, "def");
    cout << "str5 = " << str5 << endl;
    string str6 = "123456";
    string str7 = "654321";
    str6.swap(str7);
    cout << "str6 = " << str6 << endl;

    // �ַ����Ƚ�
    string str8 = "ABC";
    string str9 = "abc";
    int result = str8.compare(str9);    // ����ֵС�ڵ���-1
    cout << "result = " << result << endl;
    
    return 0;
}