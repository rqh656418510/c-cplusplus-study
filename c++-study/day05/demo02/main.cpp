/**
 * 1. �Զ��� MyString �࣬��ʵ�ָ��ֲ�����������
 */

#include "MyString.h"

int main() {

	// �Զ������вι��캯��
	MyString str1("Tom");
	MyString str2(NULL);
	MyString str3("Peter");

	// �Զ����ÿ������캯��
	MyString str4 = str1;

	// ���� "<<" �����
	cout << "str2 = " << str2 << endl;
	cout << "str4 = " << str4 << endl;
	cout << endl;

	// ���� "=" ��������������
	str4 = str3;
	cout << "str4 = " << str4 << endl;
	str4 = "Jim";
	cout << "str4 = " << str4 << endl;
	str4 = NULL;
	cout << "str4 = " << str4 << endl;
	cout << endl;

	// ���� "[]" �����
	MyString str5("David");
	str5[0] = 'F';
	cout << "str5[0] = " << str5[0] << endl;
	cout << "str5 = " << str5 << endl;
	cout << endl;

	// ���� "==" �����
	MyString str6("Aaron");
	MyString str7 = str6;
	cout << str6 << (str6 == str7 ? " = " : " != ") << str7 << endl;

	// ���� "!=" �����
	cout << str6 << (str6 != NULL ? " != " : " = ") << " NULL" << endl;
	cout << endl;

	// ���� "<" �����
	MyString str8("AAAA");
	MyString str9("BBBB");
	cout << str8 << (str8 < str9 ? " < " : " > ") << str9 << endl;
	cout << str8 << (str8 < "CCCC" ? " < " : " > ") << "CCCC" << endl;

	// ���� ">" �����
	cout << str9 << (str9 > str8 ? " > " : " < ") << str8 << endl;
	cout << str9 << (str9 > "DDDD" ? " > " : " < ") << "DDDD" << endl;
	cout << endl;

	// ���� ">>" �����
	MyString str11(5);
	cout << "�����볤��Ϊ 5 ���ַ�����" << endl;
	cin >> str11.c_str();
	cout << "str11 = " << str11 << endl;

	// MyString str4 = NULL;   ��д�������Զ������вι��캯�� `MyString(const char* p);`

	// MyString str1("AB");
	// MyString str2 = str1;
	// str2 = NULL:    ��д�������Զ����� "=" ��������صĺ��� `bool operator==(const char* p) const;`

	return 0;
}