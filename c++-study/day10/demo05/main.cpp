/*
 * 1. �쳣�������
 * a) C++ ��׼�������ļ�ʹ��
*/

#include <iostream>

using namespace std;

void input1() {
	int number;
	cout << "������һ������: ";
	cin >> number;
	cout << "�����������: " << number << endl;
}

void input2() {
	char buf[1024];
	cout << "�������ַ���: ";
	cin >> buf;		// �������ո��ʱ����ֹͣ������������
	cout << "������ַ���: ";
	cout << buf << endl;
}

void input3() {
	char ch;
	cout << "�������ַ���: ";
	while ((ch = cin.get()) != EOF)		// ���������û�����ݣ�����������
	{
		cout << ch << " ";
	}
}

void input4() {
	char a, b, c;
	cout << "�������ַ���: ";
	cin.get(a);		// ���������û�����ݣ�����������
	cin.get(b);
	cin.get(c);
	cout << a << b << c;
}

void input5() {
	char buf[256];
	cout << "�������ַ���: ";
	cin.getline(buf, 256);		// �������ո��ʱ������ֹͣ������������
	cout << buf << endl;
}

void input6() {
	char buf1[256];
	char buf2[256];
	cout << "�������ַ���:";  // �������룺abc  efghi
	cin >> buf1;
	cin.ignore(2);		// ���Ի�����������
	cin.getline(buf2, 256);
	cout << buf1 << endl;
	cout << buf2 << endl;
}

void input7() {
	char buf1[256];
	char buf2[256];
	cout << "�������ַ���:";  // �������룺abc  efghi
	cin >> buf1;
	cin.ignore(2);
	int num = cin.peek();	// �鿴�������Ƿ�������
	cout << num << endl;
	cin.getline(buf2, 256);
	cout << buf1 << endl;
	cout << buf2 << endl;
}

void input8() {
	// �ֿ�����������������ַ�
	cout << "Please, enter a number or a word: ";
	char c = std::cin.get();

	if ((c >= '0') && (c <= '9'))
	{
		int n;
		cin.putback(c);		// �����ݷŻػ�����
		cin >> n;
		cout << "You entered a number: " << n << '\n';
	}
	else
	{
		char ch;
		cin.putback(c);		// �����ݷŻػ�����
		cin.get(ch);
		cout << "You entered a character: " << ch << '\n';
	}
}

int main() {
	input8();
	return 0;
}