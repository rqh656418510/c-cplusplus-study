/*
 * 1. string�����Ĺ����븳ֵ
*/

#include <iostream>

using namespace std;

int main() {
    // Ĭ�Ϲ��캯��
    string str1;

    // �������캯��
    string str2 = str1;

    // �вι��캯��
    string str3("abced");
    string str4(5, 'f');

    // ������ֵ
    str1 = "123456";
    str2 = str3;
    str3.assign("mnopq", 3);
    str4.assign("45678", 1, 3);     // ��0��ʼ������1��ʾ��2���ַ�
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    cout << "str3 = " << str3 << endl;
    cout << "str4 = " << str4 << endl;

    return 0;
}