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

    // ��ȡ���ַ���
    string str10 = "124abc";
    string str11 = str10.substr(1, 3);
    cout << "str11 = " << str11 << endl;

    // �ַ������������
    string str12 = "abcdef";
    str12.insert(2, "123");
    cout << "str12 = " << str12 << endl;

    // �ַ���������ɾ��
    string str13 = "123456";
    str13.erase(2, 2);
    cout << "str13 = " << str13 << endl;

    // ���ַ���ȡ�� char *
    string str14 = "hijkl";
    const char *p1 = str14.c_str();
    cout << "p1 = " << p1 << endl;

    // char * ��ʽ����ת��Ϊ string
    char *p2 = "abc123";
    string str15 = p2;
    cout << "str15 = " << str15 << endl;

    // �� string ������ char* ָ����ڴ�ռ�
    char *p3 = new char[3];
    string str16 = "hello jim";
    int number = str16.copy(p3, 3, 2);
    cout << "number = " << number << endl;
    cout << "p3 = " << p3 << endl;
    delete[] p3;

    return 0;
}